// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/LoadGameUserWidget.h"

#include "SaveGameEntryUserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "Nakatomi/NakatomiGameInstance.h"

void ULoadGameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CancelButton)
	{
		CancelButton->OnClicked.AddUniqueDynamic(this, &ULoadGameUserWidget::CancelButtonOnClicked);
		CancelButton->OnClicked.AddUniqueDynamic(this, &ULoadGameUserWidget::PlayClickedSound);

		CancelButton->OnHovered.AddUniqueDynamic(this, &ULoadGameUserWidget::CancelButtonHoveredDelegate);
		CancelButton->OnHovered.AddUniqueDynamic(this, &ULoadGameUserWidget::PlayHoveredSound);

		CancelButton->OnUnhovered.AddUniqueDynamic(this, &ULoadGameUserWidget::CancelButtonUnhoveredDelegate);
		CancelButton->OnUnhovered.AddUniqueDynamic(this, &ULoadGameUserWidget::PlayUnhoveredSound);
	}

	UNakatomiGameInstance* gameInstance = Cast<UNakatomiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameInstance && IsValid(SaveGameEntryWidgetTemplate))
	{
		TArray<FNakatomiSaveFileInfo> SaveFiles = gameInstance->GetAllSaveFilesFromDisk();
		
		for (FNakatomiSaveFileInfo SaveFile : SaveFiles)
		{
			USaveGameEntryUserWidget* SaveGameEntry = WidgetTree->ConstructWidget<USaveGameEntryUserWidget>(
				SaveGameEntryWidgetTemplate, FName("SaveGameEntry"));

			SaveGameEntry->SetSaveInfo(SaveFile);
			SavedGamesScrollBox->AddChild(SaveGameEntry);
		}
	}
}

void ULoadGameUserWidget::CancelButtonOnClicked()
{
	ReturnToPreviousScreen();
}
