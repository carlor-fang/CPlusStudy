// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "KRootMotionExportCommandlet.generated.h"

UCLASS()
class UKRootMotionExportCommandlet : public UCommandlet
{
    GENERATED_BODY()

public:
    UKRootMotionExportCommandlet();
    virtual int32 Main(const FString& Params) override;
};