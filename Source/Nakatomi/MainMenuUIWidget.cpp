// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUIWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/LoadGameUserWidget.h"

void UMainMenuUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NewGameButton)
	{
		NewGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::NewGameButtonOnClicked);
		NewGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayClickedSound);
		
		NewGameButton->OnHovered.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayHoveredSound);
		NewGameButton->OnHovered.AddUniqueDynamic(this, &UMainMenuUIWidget::NewGameTextBlockHoveredDelegate);

		NewGameButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuUIWidget::NewGameTextBlockUnhoveredDelegate);
		NewGameButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayUnhoveredSound);
	}

	if (LoadGameButton)
	{
		LoadGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::LoadGameButtonOnClicked);
		LoadGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayClickedSound);
		
		LoadGameButton->OnHovered.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayHoveredSound);
		LoadGameButton->OnHovered.AddUniqueDynamic(this, &UMainMenuUIWidget::LoadGameTextBlockHoveredDelegate);

		LoadGameButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuUIWidget::LoadGameTextBlockUnhoveredDelegate);
		LoadGameButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayUnhoveredSound);
	}
	
	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::OptionsButtonOnClicked);
		OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayClickedSound);
		
		OptionsButton->OnHovered.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayHoveredSound);
		OptionsButton->OnHovered.AddUniqueDynamic(this, &UMainMenuUIWidget::OptionsTextBlockHoveredDelegate);

		OptionsButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuUIWidget::OptionsTextBlockUnhoveredDelegate);
		OptionsButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayUnhoveredSound);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::QuitButtonOnClicked);
		QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayClickedSound);
		
		QuitButton->OnHovered.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayHoveredSound);
		QuitButton->OnHovered.AddUniqueDynamic(this, &UMainMenuUIWidget::QuitTextBlockHoveredDelegate);

		QuitButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuUIWidget::QuitTextBlockUnhoveredDelegate);
		QuitButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuUIWidget::PlayUnhoveredSound);
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
	if (LoadGameMenuWidget)
	{
		currentLoadGameWidget = CreateWidget<ULoadGameUserWidget>(GetWorld(), LoadGameMenuWidget);
		currentLoadGameWidget->AddToViewport();
		currentLoadGameWidget->SetReturnScreen(this);
		this->RemoveFromParent();
	}
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
