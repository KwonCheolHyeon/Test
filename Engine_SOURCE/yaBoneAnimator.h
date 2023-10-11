#pragma once
#include "yaComponent.h"
#include "yaTexture.h"
#include "yaMesh.h"
#include "yaMaterial.h"
#include "mdStruct.h"

using namespace md::math;
using namespace md::graphics;
namespace md
{
	class StructedBuffer;
	class BoneAnimator : public Component
	{
	public:
		BoneAnimator();
		~BoneAnimator();

		void Initalize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		
		void Binds();

		void CheckBone(std::shared_ptr<Mesh> mesh);
		void SetBones(const std::vector<BoneMatrix>* bones)
		{ 
			mBones = bones; 
			mAnimaitonBoneMatrix.resize(mBones->size()); 
		}
		void SetAnimaitionClip(std::vector<BoneAnimationClip>* clips);
		void SetClipTime(int clipIdx, float time) { mAnimationUpdateTime[clipIdx] = time; };

		graphics::StructedBuffer* GetFinalBoneMatrix() { return mBoneMatrixBuffer; }
		UINT GetBoneCount() { return static_cast<UINT>(mBones->size()); }
		void ClearData();

		/// Animation Control Function Section
		void AddAnimationClip(const std::wstring& _wstrName, int _startFrame, int _endFrame
			, fbxsdk::FbxTime::EMode _frameMode = fbxsdk::FbxTime::EMode::eFrames24);

		/// 문자열이 전달되면 해당 애니메이션이 몇 번째 클립인지를 반환한다.
		/// Fail return value : -1
		int FindClipNumber(const std::string& _clibNameStr);
		int FindClipNumber(const std::wstring& _clibNameWStr);

		/// 애니메이션이 존재하는지 여부 확인
		bool CheckIfAnimationExists(UINT _clipNumber);
		// 문자열을 사용하는 함수는 성능이 느리므로 참고할 것.
		bool CheckIfAnimationExists(const std::string& _clipNameStr);
		bool CheckIfAnimationExists(const std::wstring& _clipNameWStr);

		/// 애니메이션 변경
		void ChangeAnimation(UINT _clipNumber);
		// 문자열을 사용하는 함수는 성능이 느리므로 참고할 것.
		void ChangeAnimation(const std::string& _clipNameStr);
		void ChangeAnimation(const std::wstring& _clipNameWStr);

		/// 애니메이션 루프 여부 설정
		void SetAnimationLoop(UINT _clipNumber, bool _isLoop = false);
		// 문자열을 사용하는 함수는 성능이 느리므로 참고할 것.
		void SetAnimationLoop(const std::string& _clipNameStr,   bool _isLoop = false);
		void SetAnimationLoop(const std::wstring& _clipNameWStr, bool _isLoop = false);
		//////////////////////////////////////

		/// Animation Event Control
	public:
		void SetAnimEvents(std::map<std::wstring, Events*>* _events);
		Events* FindEvents(const std::wstring& name);

		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEventRef(const std::wstring& name);
		std::function<void()>& GetEndEventRef(const std::wstring& name);
		std::function<void()>& GetEventRef(const std::wstring& name, UINT index);

		std::function<void()>* GetStartEventPtr(const std::wstring& name);
		std::function<void()>* GetCompleteEventPtr(const std::wstring& name);
		std::function<void()>* GetEndEventPtr(const std::wstring& name);
		std::function<void()>* GetEventPtr(const std::wstring& name, UINT index);

	private:
		std::map<std::wstring, Events*>* mEvents;
		//////////////////////////////////////////////////////////////////////////////////////////

	private:
		const std::vector<BoneMatrix>* mBones;
		std::vector<BoneAnimationClip>* mAnimationClips;

		std::vector<float> mAnimationUpdateTime; 
		std::vector<Matrix> mAnimaitonBoneMatrix;	//텍스처에 전달될 행렬정보
		int mFrameCount;
		double mCurrentTime;
		int mCurrentClip; // 클립 인덱스

		int mFrameIdx; //클립의 현재프레임
		int mNextFrameIdx; // 클립의 다음 프레임
		float mRatio; //프레임 사이의 비율

		graphics::StructedBuffer* mBoneMatrixBuffer; // 특정프레임의 최종행렬
		bool mbFinalMatrixUpdate;		// 최종행렬 연산 수행여부
	};
}
