// Fill out your copyright notice in the Description page of Project Settings.


#include "FGHearingSensingComponent.h"

TArray<UFGHearingSensingComponent*> UFGHearingSensingComponent::HearingComponents;

// Sets default values for this component's properties
UFGHearingSensingComponent::UFGHearingSensingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFGHearingSensingComponent::BeginPlay() {
	Super::BeginPlay();
	HearingComponents.Add(this);
}

void UFGHearingSensingComponent::BeginDestroy() {
	Super::BeginDestroy();
	HearingComponents.Remove(this);
}


// Called every frame
void UFGHearingSensingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UFGHearingSensingComponent::GetSensingTargets(TArray<UFGHearingSensingComponent*>& outTargets,
                                                   const FVector& origin) {
	
	for (UFGHearingSensingComponent* component : HearingComponents) {
		if (component == nullptr) {
			continue;
		}
		
		const float distanceMinSq = FMath::Square(component->HearingThreshold);
	
		const float distanceSquared = FVector::DistSquared(component->GetOwner()->GetActorLocation(), origin);
		
		if (distanceSquared < distanceMinSq) {
			outTargets.Add(component);
		}
	}
}
