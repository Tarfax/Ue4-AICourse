#pragma once

#include "Components/ActorComponent.h"
#include "FGVisionSensingComponent.generated.h"

class AActor;
class UFGVisionSensingTargetComponent;
class UFGVisionSensingSettings;

USTRUCT(BlueprintType)
struct FFGVisionSensingResults {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	AActor* SensedActor = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFGVisionSensingDelegate, const FFGVisionSensingResults&, Results);

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UFGVisionSensingComponent : public UActorComponent {
	GENERATED_BODY()
public:
	UFGVisionSensingComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	bool IsPointVisible(const FVector& PointToTest, const FVector& Origin, const FVector& Direction,
	                    float DistanceMinimum) const;

	FHitResult IsPointInlLineOfSight(FTransform transform);

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ETraceTypeQuery> TraceType;

	UPROPERTY(Transient)
	TArray<UFGVisionSensingTargetComponent*> SensedTargets;

	float GetVisionInRadians() const;

	UPROPERTY(BlueprintAssignable)
	FFGVisionSensingDelegate OnTargetSensed;

	UPROPERTY(BlueprintAssignable)
	FFGVisionSensingDelegate OnTargetLost;

	UPROPERTY(EditAnywhere, Category = Sensing)
	UFGVisionSensingSettings* SensingSettings = nullptr;


	UPROPERTY(EditAnywhere, Category = Debug)
	bool bDebugDrawVision = false;

	UPROPERTY(EditAnywhere, Category="Trace")
	float TraceRadius = 500.0f;

};
