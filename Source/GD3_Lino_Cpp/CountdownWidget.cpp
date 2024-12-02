// Fill out your copyright notice in the Description page of Project Settings.


#include "CountdownWidget.h"
#include "TimerManager.h"
#include "Components/TextBlock.h"

// Fonction pour démarrer le timer
void UCountdownWidget::StartTimer(float Duration)
{
	TimerDuration = Duration;

	// Démarre un timer qui appelle UpdateTimer chaque seconde
	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &UCountdownWidget::UpdateTimer, 1.0f, true);

	// Log pour indiquer que le timer a démarré
	UE_LOG(LogTemp, Warning, TEXT("Timer démarré pour %f secondes !"), TimerDuration);
}

// Fonction appelée chaque seconde pour mettre à jour le timer
void UCountdownWidget::UpdateTimer()
{
	TimerDuration--;

	// Mettre à jour l'affichage dans le TextBlock du Widget
	if (UTextBlock* TimerText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TimerTextBlock"))))
	{
		TimerText->SetText(FText::FromString(FString::Printf(TEXT("%d secondes restantes"), FMath::FloorToInt(TimerDuration))));
	}

	// Vérifie si le timer atteint zéro
	if (TimerDuration <= 0)
	{
		OnTimerComplete();
	}
}

// Fonction appelée lorsque le timer est terminé
void UCountdownWidget::OnTimerComplete()
{
	// Arrête le timer
	GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);

	// Affiche un message ou appelle une logique spécifique
	UE_LOG(LogTemp, Warning, TEXT("Finito"));
}
