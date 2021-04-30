#include "FGVisionSensingComponent.h"
#include "FGVisionSensingSettings.h"
#include "FGVisionSensingTargetComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

UFGVisionSensingComponent::UFGVisionSensingComponent() {
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UFGVisionSensingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (SensingSettings == nullptr)
		return;

	const FVector Direction = GetOwner()->GetActorForwardVector();
	const FVector Origin = GetOwner()->GetActorLocation();

	if (bDebugDrawVision) {
		FVector Right = Direction.RotateAngleAxis(SensingSettings->Angle, FVector::UpVector);
		FVector Left = Direction.RotateAngleAxis(-SensingSettings->Angle, FVector::UpVector);
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), Origin, Origin + Right * SensingSettings->DistanceMinimum,
		                                    FLinearColor::Red);
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), Origin, Origin + Left * SensingSettings->DistanceMinimum,
		                                    FLinearColor::Green);
	}

	for (int32 Index = SensedTargets.Num() - 1; Index >= 0; --Index) {
		UFGVisionSensingTargetComponent* Target = SensedTargets[Index];

		if (Target == nullptr || (Target != nullptr && Target->IsBeingDestroyed())) {
			SensedTargets.RemoveAt(Index);
			continue;
		}

		FHitResult hit = IsPointInlLineOfSight(Target->GetOwner()->GetTransform());
		if (IsPointVisible(Target->GetTargetOrigin(), Origin, Direction, SensingSettings->DistanceMinimum) == false) {
			FFGVisionSensingResults Results;
			Results.SensedActor = Target->GetOwner();
			OnTargetLost.Broadcast(Results);
			SensedTargets.RemoveAt(Index);
		}
		else if (hit.bBlockingHit == true) {
			if (hit.Actor != Target->GetOwner()) {
				FFGVisionSensingResults Results;
				Results.SensedActor = Target->GetOwner();
				OnTargetLost.Broadcast(Results);
				SensedTargets.RemoveAt(Index);
			}
		}

	}

	TArray<UFGVisionSensingTargetComponent*> ListOfTargets;

	UFGVisionSensingTargetComponent::GetSensingTargets(ListOfTargets, GetOwner()->GetActorLocation(),
	                                                   SensingSettings->DistanceMinimum);

	for (UFGVisionSensingTargetComponent* Target : ListOfTargets) {
		if (!SensedTargets.Contains(Target) &&
			IsPointVisible(Target->GetTargetOrigin(), Origin, Direction, SensingSettings->DistanceMinimum)) {

			FHitResult hit = IsPointInlLineOfSight(Target->GetOwner()->GetTransform());
			if (hit.bBlockingHit == true) {
				if (hit.Actor/*->GetName()*/ == Target->GetOwner()/*->GetName()*/) {
					UE_LOG(LogTemp, Log, TEXT("Colliding with %s"), *hit.Actor->GetName());

					SensedTargets.Add(Target);
					FFGVisionSensingResults Results;
					Results.SensedActor = Target->GetOwner();
					OnTargetSensed.Broadcast(Results);
				}
			}
		}
	}

	TArray<FHitResult> hitResults;

	// const FVector start = GetOwner()->GetActorLocation();
	// const FVector end = GetOwner()->GetActorLocation();
	//
	// const FCollisionShape collisionShape = FCollisionShape::MakeSphere(TraceRadius);
	// const bool hit = GetWorld()->SweepMultiByChannel(hitResults, start, end, FQuat::Identity, ECC_Camera, collisionShape);
	//
	// DrawDebugSphere(GetWorld(), start, TraceRadius, 50, FColor::Orange, true);
	// if (hit == true) {
	// 	for(FHitResult const HitResult : hitResults) {
	// 		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, FString::Printf(TEXT("Hit: %s"), *HitResult.Actor->GetName()));
	// 	}
	// }

}

bool UFGVisionSensingComponent::IsPointVisible(const FVector& PointToTest, const FVector& Origin,
                                               const FVector& Direction, float DistanceMinimum) const {
	if (SensingSettings == nullptr)
		return false;

	float DistanceMinimumSq = FMath::Square(DistanceMinimum);

	if (FVector::DistSquared(Origin, PointToTest) > DistanceMinimumSq) {
		return false;
	}

	const FVector DirectionToTarget = (PointToTest - Origin).GetSafeNormal();

	const float AsHalfRad = FMath::Cos(FMath::DegreesToRadians(SensingSettings->Angle));
	const float Dot = FVector::DotProduct(Direction, DirectionToTarget);

	const bool bIsValid = Dot > AsHalfRad;

	return bIsValid;
}

FHitResult UFGVisionSensingComponent::IsPointInlLineOfSight(FTransform targetTransform) {
	FVector rayLocation;
	FRotator rayRotation;
	FVector endTrace = FVector::ZeroVector;

	float raycastDistance = 500.0f;

	rayLocation = GetOwner()->GetTransform().GetLocation();
	// rayRotation = GetOwner()->.GetRotation().Rotator();
	endTrace = targetTransform.GetLocation();

	FHitResult hit;
	UKismetSystemLibrary::LineTraceSingle(GetOwner(), rayLocation, endTrace, TraceType, false, TArray<AActor*>(),
	                                      EDrawDebugTrace::ForOneFrame, hit, true);

	return hit;
}

float UFGVisionSensingComponent::GetVisionInRadians() const {
	if (SensingSettings == nullptr)
		return 0.0;

	return FMath::Cos(FMath::DegreesToRadians(SensingSettings->Angle));
}
