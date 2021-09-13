// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverVehicle.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AHoverVehicle::AHoverVehicle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VehicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("VehicleMesh"));
	VehicleMesh->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(VehicleMesh);
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bDoCollisionTest = false;
	FVector SpringArmLocation = FVector(0.0f, 0.0f, 45.0f);
	SpringArm->SetRelativeLocation(SpringArmLocation);

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);

	bReplicates = true;
	bAlwaysRelevant = true;


	VehicleMesh->SetSimulatePhysics(true);

	HoverComponentFL = CreateDefaultSubobject<UHoverVehicleComponent>(FName("HoveComponentFL"));
	HoverComponentFL->SetupAttachment(VehicleMesh);

	HoverComponentFR = CreateDefaultSubobject<UHoverVehicleComponent>(FName("HoveComponentFR"));
	HoverComponentFR->SetupAttachment(VehicleMesh);

	HoverComponentRL = CreateDefaultSubobject<UHoverVehicleComponent>(FName("HoveComponentRL"));
	HoverComponentRL->SetupAttachment(VehicleMesh);

	HoverComponentRR = CreateDefaultSubobject<UHoverVehicleComponent>(FName("HoveComponentRR"));
	HoverComponentRR->SetupAttachment(VehicleMesh);

	TrailSpawnPoint = CreateDefaultSubobject<USceneComponent>(FName("TrailSpawnPoint"));
	TrailSpawnPoint->SetupAttachment(VehicleMesh);

}

// Called when the game starts or when spawned
void AHoverVehicle::BeginPlay()
{
	Super::BeginPlay();

	HoverComponentFL->SetParentComponent(VehicleMesh);
	HoverComponentFR->SetParentComponent(VehicleMesh);
	HoverComponentRL->SetParentComponent(VehicleMesh);
	HoverComponentRR->SetParentComponent(VehicleMesh);

}


void AHoverVehicle::GetLifetimeReplicatedProps(TArray< FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHoverVehicle, Trail);
	DOREPLIFETIME(AHoverVehicle, VehicleMesh);
	DOREPLIFETIME(AHoverVehicle, ForwardForce);
	DOREPLIFETIME(AHoverVehicle, RotationForce);
}

// Called every frame
void AHoverVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

// Called to bind functionality to input
void AHoverVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &AHoverVehicle::Server_MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AHoverVehicle::Server_TurnRight);
	PlayerInputComponent->BindAction("AddTrail", EInputEvent::IE_Pressed, this, &AHoverVehicle::Server_AddTrailPressed);
	PlayerInputComponent->BindAction("AddTrail", EInputEvent::IE_Released, this, &AHoverVehicle::Server_AddTrailReleased);
}


void AHoverVehicle::Server_MoveForward_Implementation(float Axis)
{

	/*if (GEngine && Axis != 0)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("I AM NOT AUTHORITE"));*/
	//UE_LOG(LogTemp, Warning, TEXT("TRANSFORM, %f %f %f"), ForwardForce.X, ForwardForce.Y, ForwardForce.Z);

	float forceToAdd = ForwardForceToAdd * Axis;
	FVector ForwardVector = VehicleMesh->GetForwardVector();
	ForwardForce = ForwardVector * forceToAdd;
	VehicleMesh->AddForce(ForwardForce, NAME_None, true);
}

bool AHoverVehicle::Server_MoveForward_Validate(float Axis)
{
	return true;
}

void AHoverVehicle::Server_TurnRight_Implementation(float Axis)
{
	float forceToAdd = RotationForceToAdd * Axis;
	FVector RightVector = VehicleMesh->GetRightVector();
	RotationForce = RightVector * forceToAdd;

	if (Axis > 0) {
		HoverComponentFL->GetParentComponent()->AddForceAtLocation(RotationForce, HoverComponentFL->GetComponentLocation(), NAME_None);
		HoverComponentRR->GetParentComponent()->AddForceAtLocation(RotationForce * -1, HoverComponentRR->GetComponentLocation(), NAME_None);
	}
	else if (Axis < 0)
	{
		HoverComponentFR->GetParentComponent()->AddForceAtLocation(RotationForce, HoverComponentFR->GetComponentLocation(), NAME_None);
		HoverComponentRL->GetParentComponent()->AddForceAtLocation(RotationForce * -1, HoverComponentRL->GetComponentLocation(), NAME_None);
	}
}

bool AHoverVehicle::Server_TurnRight_Validate(float Axis)
{
	return true;
}

void AHoverVehicle::Server_AddTrailPressed_Implementation()
{	
	FActorSpawnParameters SpawnInfo;
	Trail = GetWorld()->SpawnActor<ATrail>(TrailSpawnPoint->GetComponentLocation(), TrailSpawnPoint->GetComponentRotation(), SpawnInfo);
	Trail->SetTrailSpawn(TrailSpawnPoint);
	Trail->setShouldGrow(true);
}

bool AHoverVehicle::Server_AddTrailPressed_Validate()
{
	return true;
}

void AHoverVehicle::Server_AddTrailReleased_Implementation()
{
	Trail->setShouldGrow(false);
}

bool AHoverVehicle::Server_AddTrailReleased_Validate()
{
	return true;
}