// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BP_FunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class HOVERVEHICLEGAME_API UBP_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Building")
		static FHitResult BuildTrace(UWorld* World, TArray<AActor*> ActorsToIgnore, FVector Start, FVector End);
};
