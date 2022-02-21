// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"

#include "ProceduralMeshActor.generated.h"

UCLASS()
class PROCEDURALMESH_API AProceduralMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralMeshActor();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Actor Body */
private:

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* Mesh;



	/** Functions */
public:
	
	void PostActorCreated();
	void PostLoad();
	//void CreateTriangle();
	void CreateFlatSquare();
	
	/** Variables */
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SquareVariables")
	int XHeight = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SquareVariables")
	int YWidth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SquareVariables")
	int XIncrement = 400;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SquareVariables")
	int YIncrement = 400;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerlinVariables")
	float Scale = 50.f;

	
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerlinVariables")
	float Amplitude = 80000.f;



	
	

};
