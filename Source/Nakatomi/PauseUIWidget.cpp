// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseUIWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"


void UPauseUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::ResumeButtonOnClicked);
		ResumeButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayHoveredSound);
	}

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::OptionsButtonOnClicked);
		OptionsButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayHoveredSound);
	}

	if (SaveButton)
	{
		SaveButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::SaveButtonOnClicked);
		SaveButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayHoveredSound);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::QuitButtonOnClicked);
		QuitButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayHoveredSound);
	}

	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::ExitGameButtonOnClicked);
		ExitGameButton->OnHovered.AddUniqueDynamic(this, &UPauseUIWidget::PlayHoveredSound);
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
	// TODO: Implement Functionality
}

void UPauseUIWidget::QuitButtonOnClicked()
{
	// TODO: Implement Functionality
}

void UPauseUIWidget::ExitGameButtonOnClicked()
{
	// TODO: We probably want to do an autosave here.

	// TODO: Add platform specific Exit requests
	// This is not a bit deal for the moment as we are only building for windows
	// For some reason the generic version does not work the same as FWindowsPlatformMisc
	FWindowsPlatformMisc::RequestExit(false);
}

void UPauseUIWidget::PlayHoveredSound()
{
	if (ButtonHoveredSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonHoveredSound);
	}
}
