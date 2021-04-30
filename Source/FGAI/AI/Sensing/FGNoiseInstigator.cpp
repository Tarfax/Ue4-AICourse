// Fill out your copyright notice in the Description page of Project Settings.


#include "FGNoiseInstigator.h"

#include "FGHearingSensingComponent.h"
#include "NoiseActor.h"

// Sets default values
UFGNoiseInstigator::UFGNoiseInstigator() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UFGNoiseInstigator::BeginPlay() {
	Super::BeginPlay();
	// SetLifeSpan(LifeSpan);
}

// Called every frame
void UFGNoiseInstigator::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFGNoiseInstigator::InstigateNoise() {

	FFGHearingSensingResults hearingData;

	hearingData.SensedActor = GetOwner();
	hearingData.SoundRadius = Radius;
	hearingData.LifeSpan = LifeSpan;

	ANoiseActor* noiseActor = GetWorld()->SpawnActor<ANoiseActor>(NoiseActor, GetOwner()->GetActorTransform());
	
	noiseActor->MakeNoise(hearingData);

	
	// if (noiseActor != nullptr) {
	// 	noiseActor->NoiseLifeTime = LifeSpan;
	// 	noiseActor->SoundRadius = Radius;
	// 	UE_LOG(LogTemp, Log, TEXT("NoiseActor is something"));
	//
	// } else {
	// 	UE_LOG(LogTemp, Log, TEXT("NoiseActor is nullptr"));
	// }

}
