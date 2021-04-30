// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoiseActor.generated.h"

struct FFGHearingSensingResults;

UCLASS()
class FGAI_API ANoiseActor : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANoiseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Noise")
	float SoundRadius;

	UPROPERTY(EditAnywhere, Category="Noise")
	float NoiseLifeTime;

	public:
	void MakeNoise(FFGHearingSensingResults hearingData);
};
