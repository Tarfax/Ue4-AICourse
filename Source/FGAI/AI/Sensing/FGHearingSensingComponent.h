// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGHearingSensingComponent.generated.h"

USTRUCT(BlueprintType)
struct FFGHearingSensingResults {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	AActor* SensedActor = nullptr;
	UPROPERTY(BlueprintReadOnly)
	float SoundRadius = 200.0f;
	UPROPERTY(BlueprintReadOnly)
	float LifeSpan = 1.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFGHearingSensingDelegate, const FFGHearingSensingResults&, Results);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FGAI_API UFGHearingSensingComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UFGHearingSensingComponent();
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FFGHearingSensingDelegate OnTargetHeard;

	UPROPERTY(EditAnywhere)
	float HearingThreshold = 1000.0f;
	
	static TArray<UFGHearingSensingComponent*> HearingComponents;
	static void GetSensingTargets(TArray<UFGHearingSensingComponent*>& outTargets, const FVector& origin);
};
