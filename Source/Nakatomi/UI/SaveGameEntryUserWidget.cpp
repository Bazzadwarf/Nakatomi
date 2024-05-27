// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/SaveGameEntryUserWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Nakatomi/NakatomiGameInstance.h"

void USaveGameEntryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (LoadSaveButton)
	{
		LoadSaveButton->OnClicked.AddUniqueDynamic(this, &USaveGameEntryUserWidget::LoadSaveButtonOnClicked);
		LoadSaveButton->OnClicked.AddUniqueDynamic(this, &USaveGameEntryUserWidget::PlayClickedSound);

		LoadSaveButton->OnHovered.AddUniqueDynamic(this, &USaveGameEntryUserWidget::LoadSaveButtonHoveredDelegate);
		LoadSaveButton->OnHovered.AddUniqueDynamic(this, &USaveGameEntryUserWidget::PlayHoveredSound);

		LoadSaveButton->OnUnhovered.AddUniqueDynamic(this, &USaveGameEntryUserWidget::LoadSaveButtonUnhoveredDelegate);
		LoadSaveButton->OnUnhovered.AddUniqueDynamic(this, &USaveGameEntryUserWidget::PlayUnhoveredSound);
	}
}

void USaveGameEntryUserWidget::SetSaveInfo(FNakatomiSaveFileInfo SaveFile)
{
	SaveFileInfo = SaveFile;
	PlayerNameTextBlock->SetText(FText::FromString(SaveFileInfo.PlayerName));
	CurrentLevelTextBlock->SetText(FText::FromString(SaveFileInfo.CurrentLevel));
	DateTimeSavedTextBlock->SetText(FText::FromString(SaveFileInfo.DateTimeSaved));
}

void USaveGameEntryUserWidget::LoadSaveButtonOnClicked()
{
	UNakatomiGameInstance* gameInstance = Cast<UNakatomiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UNakatomiSaveGame* Save = gameInstance->LoadGameFromSlot(SaveFileInfo.PlayerName);
	UGameplayStatics::OpenLevel(GetWorld(), FName(Save->LevelName));

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PlayerController->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	}

	SetIsFocusable(false);
}

void USaveGameEntryUserWidget::LoadSaveButtonHoveredDelegate()
{
	SetTextBlockHovered(PlayerNameTextBlock);
	SetTextBlockHovered(CurrentLevelTextBlock);
	SetTextBlockHovered(DateTimeSavedTextBlock);
}

void USaveGameEntryUserWidget::LoadSaveButtonUnhoveredDelegate()
{
	SetTextBlockUnhovered(PlayerNameTextBlock);
	SetTextBlockUnhovered(CurrentLevelTextBlock);
	SetTextBlockUnhovered(DateTimeSavedTextBlock);
}
