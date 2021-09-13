 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Trail.generated.h"

UCLASS()
class HOVERVEHICLEGAME_API ATrail : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrail();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int32 CallTracker = 3;

public:

	UPROPERTY(Category = Trail, BlueprintReadWrite, VisibleAnywhere, Replicated)
		bool shouldGrow;

	UPROPERTY(Category = Trail, BlueprintReadWrite, VisibleAnywhere, Replicated)
		USceneComponent* TrailSpawn;	

	UPROPERTY(Replicated)
	FTimerHandle TimerHandle;

	void setShouldGrow(bool shouldTrailGrow);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = Trail, BlueprintReadWrite, VisibleAnywhere, Replicated)
		USplineComponent* Spline;

	void SetTrailSpawn(USceneComponent* Spawn);


	void TimerFunction();
};
