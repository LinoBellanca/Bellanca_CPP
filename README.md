# Bellanca_CPP

Sur ce projet se trouve uniquement le timer.
Le timer marchait juste avant que je ferme le projet pour le mettre sur le git.
Quand je l'ai réouvert, pour quelquonque raison, la classe CountdownWidget de voulait pas être reconnue malgré avoir rebuild.

Voici le code qui marchait :

CountdownWidget.h

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



CountdownWidget.cpp

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


Ensuite, créer un widget de la classe CountdownTimer avec un canvas puis un TextBlock nommé "TimerTextBLock"

Puis créer un gamemode qui créer ce widget et lange la fonction "Start Timer" (en entrant une duration de 120 secondes)

Apparement ça serait à cause de ça (je précise que j'ai utilisé Rider) :

CONSOLE: Use build tool: C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\amd64\MSBuild.exe
Microsoft.NET.Sdk.ImportWorkloads.props(14,3): Error  : Impossible de résoudre le SDK «Microsoft.NET.SDK.WorkloadAutoImportPropsLocator». Exactement l’un des messages de sondage ci-dessous indique pourquoi nous n’avons pas pu résoudre le Kit de développement logiciel (SDK). Examinez et résolvez ce message pour spécifier correctement le Kit de développement logiciel (SDK).
  NuGetSdkResolver n’a pas résolu ce SDK, car aucune version n’était spécifiée dans le projet ou global.json.
  MSB4276: Le programme de résolution du SDK par défaut n’a pas pu résoudre le SDK «Microsoft.NET.SDK.WorkloadAutoImportPropsLocator», car le répertoire «C:\Program Files\Epic Games\UE_5.3\Engine\Binaries\ThirdParty\DotNet\6.0.302\windows\sdk\6.0.302\Sdks\Microsoft.NET.SDK.WorkloadAutoImportPropsLocator\Sdk» n’existait pas.
07:28:40 Building C:\Program Files\Epic Games\UE_5.3\Engine\Source\Programs\UnrealBuildTool\UnrealBuildTool.csproj
0>Microsoft.NET.Sdk.ImportWorkloads.props(14,38): Error MSB4236 : Le SDK 'Microsoft.NET.SDK.WorkloadAutoImportPropsLocator' spécifié est introuvable.


