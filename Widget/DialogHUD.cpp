// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DialogHUD.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/Overlay.h"

void UDialogHUD::ShowPlayerDialog(bool Value)
{
	if (Value)
	{
		PlayerDialogBox->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		PlayerDialogBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UDialogHUD::SetPlayerText(FString InName, FString InDialog)
{
	NameText->SetText(FText::FromString(InName));
	DialogText->SetText(FText::FromString(InDialog));
}

void UDialogHUD::ShowGodDialog(bool Value)
{
	if (Value)
	{
		GodDialogBox->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		GodDialogBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UDialogHUD::SetGodDialog(int32 BackgroundIndex, FString InDialog)
{
	// ������ ��
	if (BackgroundIndex == 0)
	{
		GodBG->SetColorAndOpacity(FLinearColor(0.15625f, 0.f, 0.001243f, 0.3f));
	}
	// �η��� ��
	else if (BackgroundIndex == 1)
	{
		GodBG->SetColorAndOpacity(FLinearColor(0.f, 0.107723f, 0.78125f, 0.3f));
	}
	// Ʃ�丮�� �ؽ�Ʈ
	else
	{
		GodBG->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.3f));
	}

	GodText->SetText(FText::FromString(InDialog));
}