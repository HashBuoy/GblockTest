// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "GBSimpleRandomMovementProcessor.generated.h"

/**
 * 
 */
UCLASS()
class GBLOCKTEST_API UGBSimpleRandomMovementProcessor : public UMassProcessor
{ 
private:
	GENERATED_BODY()

public:
	UGBSimpleRandomMovementProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
	
private:
	FMassEntityQuery EntityQuery;
};
