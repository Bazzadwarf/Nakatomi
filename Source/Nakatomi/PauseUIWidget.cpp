// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseUIWidget.h"

#include "NakatomiGameInstance.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"


void UPauseUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::PlayClickedSound);
		ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::ResumeButtonOnClicked);
		
		ResumeButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayHoveredSound);
		ResumeButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::ResumeTextBlockHoveredDelegate);

		ResumeButton->OnUnhovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayUnhoveredSound);
		ResumeButton->OnUnhovered.AddUniqueDynamic(this, &UPauseUIWidget::ResumeTextBlockUnhoveredDelegate);
	}

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::PlayClickedSound);
		OptionsButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::OptionsButtonOnClicked);

		OptionsButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayHoveredSound);
		OptionsButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::OptionsTextBlockHoveredDelegate);

		OptionsButton->OnUnhovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayUnhoveredSound);
		OptionsButton->OnUnhovered.AddUniqueDynamic(this, &UPauseUIWidget::OptionsTextBlockUnhoveredDelegate);
	}

	if (SaveButton)
	{
		SaveButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::PlayClickedSound);
		SaveButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::SaveButtonOnClicked);

		SaveButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayHoveredSound);
		SaveButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::SaveTextBlockHoveredDelegate);

		SaveButton->OnUnhovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayUnhoveredSound);
		SaveButton->OnUnhovered.AddUniqueDynamic(this, &UPauseUIWidget::SaveTextBlockUnhoveredDelegate);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::PlayClickedSound);
		QuitButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::QuitButtonOnClicked);

		QuitButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayHoveredSound);
		QuitButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::QuitTextBlockHoveredDelegate);

		QuitButton->OnUnhovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayUnhoveredSound);
		QuitButton->OnUnhovered.AddUniqueDynamic(this, &UPauseUIWidget::QuitTextBlockUnhoveredDelegate);
	}

	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::PlayClickedSound);
		ExitGameButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::ExitGameButtonOnClicked);

		ExitGameButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayHoveredSound);
		ExitGameButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::ExitGameTextBlockHoveredDelegate);

		ExitGameButton->OnUnhovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayUnhoveredSound);
		ExitGameButton->OnUnhovered.AddUniqueDynamic(this, &UPauseUIWidget::ExitGameTextBlockUnhoveredDelegate);
	}

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, this, EMouseLockMode::LockAlways);
		PlayerController->bShowMouseCursor = true;
	}

	SetIsFocusable(true);
}

void UPauseUIWidget::ResumeButtonOnClicked()
{
	this->RemoveFromParent();

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetPause(false);
	}
}

void UPauseUIWidget::OptionsButtonOnClicked()
{
	if (OptionsMenuWidget)
	{
		currentOptionsMenuWidget = CreateWidget<UOptionsUIWidget>(GetWorld(), OptionsMenuWidget);
		currentOptionsMenuWidget->AddToViewport();
		currentOptionsMenuWidget->SetReturnScreen(this);
		this->RemoveFromParent();
	}
}

void UPauseUIWidget::SaveButtonOnClicked()
{
	UNakatomiGameInstance* gameInstance = Cast<UNakatomiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameInstance->SaveGame())
	{
		PlayAnimation(SaveConfirmedAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
	}
}

void UPauseUIWidget::QuitButtonOnClicked()
{
	// TODO: Replace this is a menu to confirm the user wants to start a new game
	if (!MainMenuLevel.IsNull())
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MainMenuLevel);	
	}

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, this, EMouseLockMode::LockAlways);
		PlayerController->bShowMouseCursor = true;
	}

	SetIsFocusable(true);
}

void UPauseUIWidget::ExitGameButtonOnClicked()
{
	// TODO: We probably want to do an autosave here.

	// TODO: Add platform specific Exit requests
	// This is not a bit deal for the moment as we are only building for windows
	// For some reason the generic version does not work the same as FWindowsPlatformMisc
	FWindowsPlatformMisc::RequestExit(false);
}
