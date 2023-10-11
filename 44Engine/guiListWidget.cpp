﻿#include "guiListWidget.h"


namespace gui
{
	ListWidget::ListWidget()
		: Widget()
		, mEventWidget(nullptr)
		, mListIndex(-1)
	{
		SetName("ListWidget");
		SetState(eState::Paused);
		SetSize(ImVec2(200.0f, 200.0f));

	}

	ListWidget::~ListWidget()
	{
	}

	void ListWidget::Update()
	{

		if (ImGui::BeginListBox("##ListBox", GetSize()))
		{
			WindowFocus(true);
			for (size_t i = 0; i < mResourceList.size(); i++)
			{
				bool selectable = (mListIndex == i);
				if (ImGui::Selectable(mResourceList[i].c_str(), &selectable))
				{
					mListIndex = static_cast<int>(i);
				}

				if (selectable)
				{
					ImGui::SetItemDefaultFocus();
				}
				
				// 해당 아이템이 더블클릭 되었다면
				if (ImGui::IsItemHovered() 
					&& ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					if (mEventWidget && mEvent)
					{
						mEvent(mResourceList[i].c_str());
					}
					Close();
				}

			}
			ImGui::EndListBox();
		}
	}

	void ListWidget::Close()
	{
		SetState(eState::Paused);
		mResourceList.clear();

		WindowFocus(false);
	}

	void ListWidget::SetItemList(const std::vector<std::wstring>& list)
	{
		for (auto wName : list)
		{
			std::string name = WStringToString(wName);
			mResourceList.push_back(name);
		}
	}

	void ListWidget::SetItemList(const std::vector<std::string>& list)
	{
		mResourceList = list;
	}
}
