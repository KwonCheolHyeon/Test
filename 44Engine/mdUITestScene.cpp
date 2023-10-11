#include "mdUITestScene.h"

#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaObject.h"
#include "yaRenderer.h"
#include "yaLight.h"

#include "mdUIBase.h"
#include "mdUIProgressBar.h"
#include "mdUIAlphaObject.h"
#include "mdUIEquipment.h"

#include "mdUIButton.h"
#include "mdUIInventory.h"
#include "mdMouseObject.h"
#include "mdUIControl.h"

#include "yaCollisionManager.h"
namespace md 
{
	UITestScene::UITestScene()
		: Scene(eSceneType::UITestScene)
	{
	}
	
	UITestScene::~UITestScene()
	{
	}

	void UITestScene::Initalize()
	{
		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		cameraObj->SetName(L"MainCamera");
		cameraObj->SetPosition(Vector3(0.0f, 10.0f, -50.0f));
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetCameraType(Camera::eCameraType::NoneUI);
		//cameraObj->AddComponent<CameraScript>();
		renderer::mainCamera = cameraComp;

		GameObject* uiCameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		uiCameraObj->SetName(L"UICamera");
		uiCameraObj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		//uiCameraObj->GetTransform()->SetParent(cameraObj->GetTransform());
		cameraComp = uiCameraObj->AddComponent<Camera>();
		//uiCameraObj->AddComponent<CameraScript>();
		cameraComp->SetCameraType(Camera::eCameraType::UI);
		renderer::mainUICamera = cameraComp;

		
		
		UIControl* uiControl = object::InstantiateUI<UIControl>();
		uiControl->SetName(L"uiControl");
			
		

		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Light);
			directionalLight->SetName(L"directionalLight");
		
			directionalLight->SetPosition(Vector3(-0.0f, 0.0f, 0.0f));
			directionalLight->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			lightComp->SetSpecular(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			lightComp->SetAmbient(Vector4(0.15f, 0.15f, 0.15f, 1.0f));
		}
		
		{
			UIBase* hotBarBackGroundObject = object::InstantiateUI<UIBase>();
			hotBarBackGroundObject->SetName(L"HotBarBackGround");
			hotBarBackGroundObject->SetMaterial(L"hotbarBackgroundMat");
			hotBarBackGroundObject->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -830.0f, 3.5f));
			hotBarBackGroundObject->GetComponent<Transform>()->SetScale(Vector3(3600.0f, 180.0f, 1.f));
		}
		
		{//상자 담는 칸
			UIBase* bigslotObject = object::InstantiateUI<UIBase>();
			bigslotObject->SetName(L"bigslot");
			bigslotObject->SetMaterial(L"bigslotMat");
			bigslotObject->GetComponent<Transform>()->SetPosition(Vector3(-1450.0f, -750.0f, 3.5f));
			bigslotObject->GetComponent<Transform>()->SetScale(Vector3(280.f, 160.f, 1.f));
		}
		{//상자
			UIBase* BoxIconObject = object::InstantiateUI<UIBase>();
			BoxIconObject->SetName(L"BoxIcon");
			BoxIconObject->SetMaterial(L"BoxIconMat");
			BoxIconObject->GetComponent<Transform>()->SetPosition(Vector3(-1450.0f, -750.0f, 3.5f));
			BoxIconObject->GetComponent<Transform>()->SetScale(Vector3(190.f, 100.f, 1.f));
		}
		
		{//아이템 슬롯 1
			UIBase* square_frameObject1 = object::InstantiateUI<UIBase>();
			square_frameObject1->SetName(L"square_frame1");
			square_frameObject1->SetMaterial(L"square_frameMat");
			/*square_frameObject1->GetComponent<Transform>()->SetPosition(Vector3(-1.55f, -1.6f, 3.5f));
			square_frameObject1->GetComponent<Transform>()->SetScale(Vector3(0.4f, 0.4f, 1.f));*/
			square_frameObject1->GetComponent<Transform>()->SetPosition(Vector3(-1100.0f, -740.0f, 3.5f));
			square_frameObject1->GetComponent<Transform>()->SetScale(Vector3(300.f, 180.f, 1.f));
		}

		{//아이템 슬롯 아이템
			UIEquipment* emptySlot = object::InstantiateUI<UIEquipment>();
			emptySlot->SetItemType(0);
			emptySlot->SetName(L"square_frame1");
			emptySlot->SetMaterial(L"EmptyEquipMat");
			emptySlot->GetComponent<Transform>()->SetPosition(Vector3(-1100.0f, -740.0f, 3.5f));
			emptySlot->SetScale(Vector3(100.f, 50.f, 1.f));
		}
		
		
		
		{//아이템 슬롯 2
			UIBase* square_frameObject2 = object::InstantiateUI<UIBase>();
			square_frameObject2->SetName(L"square_frame2");
			square_frameObject2->SetMaterial(L"square_frameMat");
			square_frameObject2->GetComponent<Transform>()->SetPosition(Vector3(-750.0f, -740.0f, 3.5f));
			square_frameObject2->GetComponent<Transform>()->SetScale(Vector3(300.f, 180.f, 1.f));
		}
		{//아이템 슬롯 아이템
			UIEquipment* emptySlot = object::InstantiateUI<UIEquipment>();
			emptySlot->SetItemType(0);
			emptySlot->SetName(L"square_frame1");
			emptySlot->SetMaterial(L"EmptyEquipMat");
			emptySlot->GetComponent<Transform>()->SetPosition(Vector3(-750.0f, -740.0f, 3.5f));
			emptySlot->SetScale(Vector3(100.f, 50.f, 1.f));
		}
		
		{//아이템 슬롯 3
			UIBase* square_frameObject3 = object::InstantiateUI<UIBase>();
			square_frameObject3->SetName(L"square_frame3");
			square_frameObject3->SetMaterial(L"square_frameMat");
			square_frameObject3->GetComponent<Transform>()->SetPosition(Vector3(-400.0f, -740.0f, 3.5f));
			square_frameObject3->GetComponent<Transform>()->SetScale(Vector3(300.f, 180.f, 1.f));
		}
		{//아이템 슬롯 아이템
			UIEquipment* emptySlot = object::InstantiateUI<UIEquipment>();
			emptySlot->SetItemType(0);
			emptySlot->SetName(L"square_frame1");
			emptySlot->SetMaterial(L"EmptyEquipMat");
			emptySlot->GetComponent<Transform>()->SetPosition(Vector3(-400.0f, -740.0f, 3.5f));
			emptySlot->SetScale(Vector3(100.f, 50.f, 1.f));
		
		}
		
		{// 체력 프레임
			UIBase* Heart_frameObject = object::InstantiateUI<UIBase>();
			Heart_frameObject->SetName(L"Heart_frame");
			Heart_frameObject->SetMaterial(L"Hotbar_HeartframeMat");
			Heart_frameObject->GetComponent<Transform>()->SetPosition(Vector3(0.f, -750.0f, 3.5f));
			Heart_frameObject->GetComponent<Transform>()->SetScale(Vector3(600.0f, 300.f, 1.f));
		}
		{// 체력 color
			ProgressBar* Hotbar_HeartframeMat = object::InstantiateUI<ProgressBar>();
			Hotbar_HeartframeMat->SetName(L"Hotbar_Heartframe");
			Hotbar_HeartframeMat->SetMaterial(L"HeartColorMat");
			Hotbar_HeartframeMat->GetComponent<Transform>()->SetPosition(Vector3(0.f, -750.0f, 3.5f));
			Hotbar_HeartframeMat->GetComponent<Transform>()->SetScale(Vector3(600.0f, 300.f, 1.f));

			uiControl->SetProgressBar(Hotbar_HeartframeMat);
		
		}
		{// 체력 Damege Frame
			UIAlphaObject* HeartframeMat = object::InstantiateUI<UIAlphaObject>();
			HeartframeMat->SetName(L"Hotbar_HeartframeDamage");
			HeartframeMat->SetMaterial(L"HeartDamageMat");
			HeartframeMat->GetComponent<Transform>()->SetPosition(Vector3(0.f, -750.0f, 3.5f));
			HeartframeMat->GetComponent<Transform>()->SetScale(Vector3(600.0f, 300.f, 1.f));

			uiControl->SetDamegeFrame(HeartframeMat);
		}
		
		
		{// 포션 아이템 슬롯
			UIBase* square_frameObject4 = object::InstantiateUI<UIBase>();
			square_frameObject4->SetName(L"square_frame4");
			square_frameObject4->SetMaterial(L"square_frameMat");
			square_frameObject4->GetComponent<Transform>()->SetPosition(Vector3(400.0f, -740.0f, 3.5f));
			square_frameObject4->GetComponent<Transform>()->SetScale(Vector3(300.f, 180.f, 1.f));
		}
		
		{// 포션 아이템 이미지
			UIBase* square_frameObject4 = object::InstantiateUI<UIBase>();
			square_frameObject4->SetName(L"potionImage");
			square_frameObject4->SetMaterial(L"potion_emptyMat");
			square_frameObject4->SetPosition(Vector3(400.0f, -740.0f, 3.5f));
			square_frameObject4->SetScale(Vector3(200.f, 120.f, 1.f));
		}


		{// 쿨타임
			ProgressBar* coolTimeBar = object::InstantiateUI<ProgressBar>();
			coolTimeBar->SetType(3);
			coolTimeBar->SetName(L"CoolTimeframe");
			coolTimeBar->SetMaterial(L"coolTimeMat");
			coolTimeBar->SetPosition(Vector3(400.0f, -740.0f, 3.5f));
			coolTimeBar->SetScale(Vector3(300.f, 180.f, 1.f));

			uiControl->SetProgressBar(coolTimeBar);
		}
		
		
		{// 미니맵 담는 칸
			UIBase* bigslotObject2 = object::InstantiateUI<UIBase>();
			bigslotObject2->SetName(L"bigslot");
			bigslotObject2->SetMaterial(L"bigslotMat");
			bigslotObject2->GetComponent<Transform>()->SetPosition(Vector3(730.0f, -740.0f, 3.5f));
			bigslotObject2->GetComponent<Transform>()->SetScale(Vector3(280.f, 160.f, 1.f));
		}
		{//미니 맵 아이콘
			UIBase* miniMapObject = object::InstantiateUI<UIBase>();
			miniMapObject->SetName(L"MiniMapIcon");
			miniMapObject->SetMaterial(L"map_IconMat");
			miniMapObject->GetComponent<Transform>()->SetPosition(Vector3(730.0f, -740.0f, 3.5f));
			miniMapObject->GetComponent<Transform>()->SetScale(Vector3(190.f, 100.f, 1.f));
		}
		
		{//Rolling HotBar
			UIBase* bigslotObject2 = object::InstantiateUI<UIBase>();
			bigslotObject2->SetName(L"hotbar_indentslot_center");
			bigslotObject2->SetMaterial(L"hotbar_indentslot_centerMat");
			bigslotObject2->SetPosition(Vector3(1030.0f, -770.0f, 3.5f));
			bigslotObject2->SetScale(Vector3(200.f, 100.f, 1.f));
		}
		
		{// Rolling
			ProgressBar* rollingObject = object::InstantiateUI<ProgressBar>();
			rollingObject->SetType(1);
			rollingObject->SetName(L"rolling_Icon");
			rollingObject->SetMaterial(L"rolling_iconMat");
			rollingObject->SetPosition(Vector3(1030.0f, -770.0f, 3.5f));
			rollingObject->SetScale(Vector3(180.f, 80.f, 1.f));

			uiControl->SetProgressBar(rollingObject);
		}
		
		{//arrow_slot 슬롯 
			UIBase* arrow_slotObject = object::InstantiateUI<UIBase>();
			arrow_slotObject->SetName(L"arrow_slot");
			arrow_slotObject->SetMaterial(L"arrow_slotMat");
			arrow_slotObject->SetPosition(Vector3(1330.0f, -770.0f, 3.5f));
			arrow_slotObject->SetScale(Vector3(300.f, 200.f, 1.f));
		}
		{//아이템 슬롯 아이템
			UIEquipment* emptyArrowObject = object::InstantiateUI<UIEquipment>();
			emptyArrowObject->SetItemType(1);
			emptyArrowObject->SetName(L"emptyArrow");
			emptyArrowObject->SetMaterial(L"EmptyEquipMat");
			emptyArrowObject->SetPosition(Vector3(1330.0f, -770.0f, 3.5f));
			emptyArrowObject->SetScale(Vector3(280.f, 180.f, 1.f));
		}

		UIInventory* uiInventory = object::InstantiateUI<UIInventory>();
		uiInventory->SetName(L"Inventory");
		uiInventory->SetMaterial(L"InvenBackGroundMat");
		uiInventory->SetPosition(Vector3(0.f, 0.f, 3.5f));
		uiInventory->SetScale(Vector3(5750.f, 1850.f, 1.f));

		Vector3 equipSlotSize = Vector3(350.f, 200.f, 1.f);
		{//장비창 0
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
			
			buttonTest->SetName(L"button0");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-3.2f, 1.f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.1f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-2400.f, 400.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(equipSlotSize);
			buttonTest->SetButtonImage(0, 0, 0);

			uiInventory->SetButtons(buttonTest);
		}

		{//장비창1
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button1");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-2.4f, 1.2f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-1700.f, 500.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(equipSlotSize);
			buttonTest->SetButtonImage(0, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//장비창2
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button2");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-1.6f, 1.0f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.35f, 0.35f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-1000.f, 400.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(equipSlotSize);
			buttonTest->SetButtonImage(0, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//장비창3
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button3");
			buttonTest->SetMaterial(L"UIButtonMat");
		
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-3.f, -1.6f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.35f, 0.35f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-2150.f, -700.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(equipSlotSize);
			buttonTest->SetButtonImage(0, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		{//장비창4
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button4");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-2.4f, -1.6f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.35f, 0.35f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-1700.f, -700.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(equipSlotSize);
			buttonTest->SetButtonImage(0, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		{//장비창5
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button5");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-1.8f, -1.6f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.35f, 0.35f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-1250.f, -700.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(equipSlotSize);
			buttonTest->SetButtonImage(0, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		Vector3 inventorySlotSize = Vector3(450.f, 250.f, 1.f);
		{//인벤토리 6
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button6");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-1.f, 1.f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-400.f, 420.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(inventorySlotSize);
			buttonTest->SetButtonImage(1, 0, 1);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		
		{//인벤토리 7
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button7");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-0.4f, 1.f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(100.f, 420.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(inventorySlotSize);
			buttonTest->SetButtonImage(1, 0, 2);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		
		{//인벤토리 8
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button8");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(0.2f, 1.f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(600.f, 420.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(inventorySlotSize);
			buttonTest->SetButtonImage(1, 0, 3);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//인벤토리 9
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button9");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-1.f, 0.4f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-400.f, 140.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(inventorySlotSize);
			buttonTest->SetButtonImage(1, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//인벤토리 10
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button10");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-0.4f, 0.4f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(100.f, 140.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(inventorySlotSize);
			buttonTest->SetButtonImage(1, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//인벤토리11
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button11");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(0.2f, 0.4f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(600.f, 140.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(inventorySlotSize);
			buttonTest->SetButtonImage(1, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//인벤토리 12
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button12");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-1.f, -0.2f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-400.f, -140.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(inventorySlotSize);
			buttonTest->SetButtonImage(1, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//인벤토리 13
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button13");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-0.4f, -0.2f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(100.f, -140.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(inventorySlotSize);
			buttonTest->SetButtonImage(1, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//인벤토리14
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button14");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(0.2f, -0.2f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(600.f, -140.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(inventorySlotSize);
			buttonTest->SetButtonImage(1, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//인벤토리 15
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button15");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-1.f, -0.8f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-400.f, -420.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(inventorySlotSize);
			buttonTest->SetButtonImage(1, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//인벤토리 16
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button16");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-0.4f, -0.8f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(100.f, -420.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(inventorySlotSize);
			buttonTest->SetButtonImage(1, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//인벤토리17
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button17");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(0.2f, -0.8f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(600.0f, -420.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(inventorySlotSize);
			buttonTest->SetButtonImage(1, 0, 0);
		
			uiInventory->SetButtons(buttonTest);
		}
		
		Vector3 categorySize = Vector3(80.f, 50.f, 1.f);
		{//카테고리 18
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button18");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-1.2f, 1.4f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.1f, 0.1f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-600.f, 620.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(categorySize);
			buttonTest->SetHowManyImage(1);
			buttonTest->SetButtonImage(2, 0, 0);//카테고리는 가운데 안써도됨
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//카테고리 19
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button19");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-0.8f, 1.4f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.1f, 0.1f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-300.f, 620.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(categorySize);
			buttonTest->SetHowManyImage(1);
			buttonTest->SetButtonImage(2, 0, 1);//카테고리는 가운데 안써도됨
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//카테고리 20
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button20");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(-0.4f, 1.4f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.1f, 0.1f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(0.f, 620.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(categorySize);
			buttonTest->SetHowManyImage(1);
			buttonTest->SetButtonImage(2, 0, 2);//카테고리는 가운데 안써도됨
		
			uiInventory->SetButtons(buttonTest);
		}
		
		{//카테고리 21
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button20");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(0.f, 1.4f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.1f, 0.1f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(300.f, 620.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(categorySize);
			buttonTest->SetHowManyImage(1);
			buttonTest->SetButtonImage(2, 0, 3);//카테고리는 가운데 안써도됨
		
			uiInventory->SetButtons(buttonTest);
		}
		{//카테고리 22
			UIButton* buttonTest = object::InstantiateUI<UIButton>();
		
			buttonTest->SetName(L"button22");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(0.4f, 1.4f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(0.1f, 0.1f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(600.f, 620.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(categorySize);
			buttonTest->SetHowManyImage(1);
			buttonTest->SetButtonImage(2, 0, 4);//카테고리는 가운데 안써도됨
		
			//buttonTest->SetPhysics();

			uiInventory->SetButtons(buttonTest);
		}
		
		{//나가기 버튼 23
			UIButton* buttonTest = object::InstantiateUI<UIButton>();

			buttonTest->SetName(L"button23");
			buttonTest->SetMaterial(L"UIButtonMat");
			//buttonTest->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 1.5f, 3.5f));
			//buttonTest->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.f, 1.f));
			buttonTest->GetComponent<Transform>()->SetPosition(Vector3(2500.0f, 800.f, 3.5f));
			buttonTest->GetComponent<Transform>()->SetScale(Vector3(150.f, 100.f, 1.f));
			buttonTest->SetHowManyImage(1);
			buttonTest->SetButtonImage(3, 0, 0);//카테고리는 가운데 안써도됨

			//buttonTest->SetPhysics();

			uiInventory->SetButtons(buttonTest);

		}
		uiInventory->InitItemVector();
		{
			MouseObject* mouseObject = object::InstantiateUI<MouseObject>();

			mouseObject->SetName(L"button24");
			mouseObject->SetMaterial(L"MouseCursorMat");

			mouseObject->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 3.5f));
			mouseObject->GetComponent<Transform>()->SetScale(Vector3(50.0f, 50.0f, 1.f));
			mouseObject->SetInventory(uiInventory);
		}
		
		uiControl->SetInventory(uiInventory);

		Scene::Initalize();
	}
	
	void UITestScene::Update()
	{

		Scene::Update();
	}
	
	void UITestScene::FixedUpdate()
	{

		Scene::FixedUpdate();
	}
	
	void UITestScene::Render()
	{

		Scene::Render();
	}
	
	void UITestScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void UITestScene::OnExit()
	{
		Scene::OnExit();
	}
}
