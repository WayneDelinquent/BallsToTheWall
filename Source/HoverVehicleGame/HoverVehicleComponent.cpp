// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverVehicleComponent.h"
#include "BP_FunctionLibrary.h"

// Sets default values for this component's properties
UHoverVehicleComponent::UHoverVehicleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHoverVehicleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	World = GetWorld();

}


// Called every frame
void UHoverVehicleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Start = GetComponentLocation();

	FVector End = HoverHeight * -1 * GetUpVector() + GetComponentLocation();
	// ...	
	FHitResult OutHit = UBP_FunctionLibrary::BuildTrace(World, ActorsToIgnore, Start, End);

	float lerp = FMath::Lerp(HoverForce, 0.0f, (OutHit.Distance / HoverHeight));
	FVector ForceToAdd = lerp * OutHit.ImpactNormal;
	ParentComponent->AddForceAtLocation(ForceToAdd, GetComponentLocation(), NAME_None);
	ParentComponent->SetLinearDamping(LinearDamping);
	ParentComponent->SetAngularDamping(AngularDamping);
}

void UHoverVehicleComponent::SetParentComponent(UPrimitiveComponent* Parent)
{
	ParentComponent = Parent;
	ActorsToIgnore.Add(Parent->GetOwner());
}

UPrimitiveComponent* UHoverVehicleComponent::GetParentComponent()
{
	return ParentComponent;
}