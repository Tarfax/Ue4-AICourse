// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseActor.h"
#include "FGHearingSensingComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ANoiseActor::ANoiseActor() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANoiseActor::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void ANoiseActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ANoiseActor::MakeNoise(FFGHearingSensingResults hearingData) {
	TArray<UFGHearingSensingComponent*> hearingComponents;

	SetLifeSpan(hearingData.LifeSpan);

	UFGHearingSensingComponent::GetSensingTargets(hearingComponents, GetActorLocation());

	for (UFGHearingSensingComponent* component : hearingComponents) {
		UE_LOG(LogTemp, Log, TEXT("Component heard a noise: %s"), *component->GetOwner()->GetName());
		component->OnTargetHeard.Broadcast(hearingData);
	}

	const FVector Origin = GetActorLocation();
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Origin, hearingData.SoundRadius, 12, FLinearColor::Yellow, hearingData.LifeSpan);
	UE_LOG(LogTemp, Log, TEXT("NoiseActor Begin Play"));

}
