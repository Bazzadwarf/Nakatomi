// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUIWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NewGameButton)
	{
		NewGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::NewGameButtonOnClicked);
		NewGameButton->OnHovered.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayHoveredSound);
	}

	if (LoadGameButton)
	{
		LoadGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::LoadGameButtonOnClicked);
		LoadGameButton->OnHovered.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayHoveredSound);
	}
	
	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::OptionsButtonOnClicked);
		OptionsButton->OnHovered.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayHoveredSound);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::QuitButtonOnClicked);
		QuitButton->OnHovered.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayHoveredSound);
	}

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, this, EMouseLockMode::LockAlways);
		PlayerController->bShowMouseCursor = true;
	}
}

void UMainMenuUIWidget::NewGameButtonOnClicked()
{
	// TODO: Replace this is a menu to confirm the user wants to start a new game
	if (!NewGameLevel.IsNull())
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), NewGameLevel);	
	}

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PlayerController->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	}

	SetIsFocusable(false);
}

void UMainMenuUIWidget::LoadGameButtonOnClicked()
{
	// TODO: Implement Functionality
}

void UMainMenuUIWidget::OptionsButtonOnClicked()
{
	if (OptionsMenuWidget)
	{
		currentOptionsMenuWidget = CreateWidget<UOptionsUIWidget>(GetWorld(), OptionsMenuWidget);
		currentOptionsMenuWidget->AddToViewport();
		currentOptionsMenuWidget->SetReturnScreen(this);
		this->RemoveFromParent();
	}
}

void UMainMenuUIWidget::QuitButtonOnClicked()
{
	// TODO: We probably want to do an autosave here.

	// TODO: Add platform specific Exit requests
	// This is not a bit deal for the moment as we are only building for windows
	// For some reason the generic version does not work the same as FWindowsPlatformMisc
	FWindowsPlatformMisc::RequestExit(false);
}

void UMainMenuUIWidget::PlayHoveredSound()
{
	if (ButtonHoveredSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonHoveredSound);
	}
}
