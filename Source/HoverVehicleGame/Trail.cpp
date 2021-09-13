// Fill out your copyright notice in the Description page of Project Settings.


#include "Trail.h"
#include "Net/UnrealNetwork.h"
#include "Math/Vector.h"

// Sets default values
ATrail::ATrail()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Spline = CreateDefaultSubobject<USplineComponent>(FName("TrailSpline"));
	Spline->SetupAttachment(RootComponent);
	Spline->SetIsReplicated(true);

	bReplicates = true;
	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void ATrail::BeginPlay()
{
	Super::BeginPlay();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, shouldGrow ? "True" : "False");
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrail::TimerFunction, 0.075, true, 0.0f);

	Spline->ClearSplinePoints();
	if (IsValid(TrailSpawn))
	{
		Spline->AddSplinePoint(TrailSpawn->GetComponentLocation(), ESplineCoordinateSpace::World, true);
	}
}

void ATrail::GetLifetimeReplicatedProps(TArray< FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATrail, shouldGrow);
	DOREPLIFETIME(ATrail, TrailSpawn);
	DOREPLIFETIME(ATrail, Spline);
	DOREPLIFETIME(ATrail, TimerHandle);
}

// Called every frame
void ATrail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrail::setShouldGrow(bool shouldTrailGrow)
{
	shouldGrow = shouldTrailGrow;
}

void ATrail::SetTrailSpawn(USceneComponent* Spawn)
{
	TrailSpawn = Spawn;
}

void ATrail::TimerFunction()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("TrailSpawn %d"), IsValid(TrailSpawn)));	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Should Grow %d"), shouldGrow));

	if (IsValid(TrailSpawn) && shouldGrow) {
		FVector SpawnLocation = TrailSpawn->GetComponentLocation();
		FVector SplineLocation = Spline->GetLocationAtSplinePoint(Spline->GetNumberOfSplinePoints(), ESplineCoordinateSpace::World);

		float Distance = FVector::Dist(SpawnLocation, SplineLocation);
		if (Distance > 25)
		{
			Spline->AddSplinePoint(TrailSpawn->GetComponentLocation(), ESplineCoordinateSpace::World, true);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}

	/*CallTracker--;

	if (CallTracker == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Loop Finished"), GetWorldTimerManager().ClearTimer(TimerHandle);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Calling Timer");
	}*/

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("CALLS REMAINING: %d"), CallTracker));
}
