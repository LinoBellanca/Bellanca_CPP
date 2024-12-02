// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CountdownWidget.generated.h"

/**
 * 
 */
UCLASS()
class GD3_LINO_CPP_API UCountdownWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// Fonction que tu appelleras pour démarrer le timer
	UFUNCTION(BlueprintCallable)
	void StartTimer(float Duration);

private:
	// Handle pour gérer le timer
	FTimerHandle CountdownTimerHandle;

	// Durée du timer en secondes
	float TimerDuration;

	// Fonction appelée chaque seconde pour mettre à jour le timer
	UFUNCTION()
	void UpdateTimer();

	// Fonction appelée lorsque le timer est terminé
	void OnTimerComplete();
};
