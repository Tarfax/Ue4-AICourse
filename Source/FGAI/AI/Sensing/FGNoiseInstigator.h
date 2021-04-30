// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "FGNoiseInstigator.generated.h"

class ANoiseActor;

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class FGAI_API UFGNoiseInstigator : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UFGNoiseInstigator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;
	float Radius = 1000.0f;
	float LifeSpan = 1.2f;
	
	
	UFUNCTION(BlueprintCallable)
	virtual void InstigateNoise();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ANoiseActor> NoiseActor;

	
	
};
