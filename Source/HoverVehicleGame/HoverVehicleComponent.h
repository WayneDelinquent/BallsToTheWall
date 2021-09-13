// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HoverVehicleComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HOVERVEHICLEGAME_API UHoverVehicleComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHoverVehicleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UWorld* World;

	TArray<AActor*> ActorsToIgnore;

	UPrimitiveComponent* ParentComponent;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetParentComponent(UPrimitiveComponent* Parent);

	UPrimitiveComponent* GetParentComponent();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float HoverHeight;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float HoverForce;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float LinearDamping;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float AngularDamping;
};
