// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "HoverVehicleComponent.h"
#include "Trail.h"
#include "HoverVehicle.generated.h"

UCLASS()
class HOVERVEHICLEGAME_API AHoverVehicle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHoverVehicle();

	//AHoverVehicle::AHoverVehicle(const class FPostConstructInitializeProperties& PCIP)

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty>& OutLifetimeProps) const;


	UPROPERTY(Category = Camera, BlueprintReadWrite, VisibleAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(Category = Camera, BlueprintReadWrite, VisibleAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(Category = Vehicle, BlueprintReadWrite, VisibleAnywhere, Replicated)
		UStaticMeshComponent* VehicleMesh;

	UPROPERTY(Category = Vehicle, BlueprintReadWrite, VisibleAnywhere)
		UHoverVehicleComponent* HoverComponentFL;
	UPROPERTY(Category = Vehicle, BlueprintReadWrite, VisibleAnywhere)
		UHoverVehicleComponent* HoverComponentFR;
	UPROPERTY(Category = Vehicle, BlueprintReadWrite, VisibleAnywhere)
		UHoverVehicleComponent* HoverComponentRL;
	UPROPERTY(Category = Vehicle, BlueprintReadWrite, VisibleAnywhere)
		UHoverVehicleComponent* HoverComponentRR;

	UPROPERTY(Category = Vehicle, BlueprintReadWrite, VisibleAnywhere)
		USceneComponent* TrailSpawnPoint;

	UPROPERTY(Category = Trail, BlueprintReadWrite, VisibleAnywhere, Replicated)
		ATrail* Trail;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float ForwardForceToAdd;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float RotationForceToAdd;

	UPROPERTY(Replicated)
		FVector ForwardForce;
	UPROPERTY(Replicated)
		FVector RotationForce;

	UFUNCTION(Server, reliable, WithValidation)
		void Server_MoveForward(float Axis);

	UFUNCTION(Server, reliable, WithValidation)
		void Server_TurnRight(float Axis);

	UFUNCTION(Server, reliable, WithValidation)
		void Server_AddTrailPressed();

	UFUNCTION(Server, reliable, WithValidation)
		void Server_AddTrailReleased();
};
