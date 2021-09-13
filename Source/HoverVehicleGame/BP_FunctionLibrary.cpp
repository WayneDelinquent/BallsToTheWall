// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_FunctionLibrary.h"

FHitResult UBP_FunctionLibrary::BuildTrace(UWorld* World, TArray<AActor*> ActorsToIgnore, FVector Start, FVector End)
{
	const FName TraceTag("MyTraceTag");

	World->DebugDrawTraceTag = TraceTag;

	struct FHitResult OutHit = FHitResult();
	FVector WorldLocation;	

	FCollisionQueryParams Params;
	Params.AddIgnoredActors(ActorsToIgnore);
	Params.TraceTag = TraceTag;
	const FCollisionResponseParams& ResponseParam();
	World->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility, Params);

	return OutHit;
}