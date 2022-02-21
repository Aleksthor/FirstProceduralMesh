// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralMeshActor.h"

// Sets default values ; Unreal Constructor
AProceduralMeshActor::AProceduralMeshActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Normal creating a subobject setting it the root
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	Mesh->SetupAttachment(GetRootComponent());
	// Mulit-thread PhysX cooking
	Mesh->bUseAsyncCooking = true;
	
}

// Called when the game starts or when spawned : Unreal BeginPlay
void AProceduralMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame : Unreal Tick
void AProceduralMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// This is called when actor is spawned (at runtime or when you drop it into the world in editor)
void AProceduralMeshActor::PostActorCreated()
{
	Super::PostActorCreated();
	CreateFlatSquare();
}

// This is called when actor is already in level and map is opened
void AProceduralMeshActor::PostLoad()
{
	Super::PostLoad();
	CreateFlatSquare();
}

//void AProceduralMeshActor::CreateTriangle()
//{
//	TArray<FVector> vertices;
//	vertices.Add(FVector(0, 0, 0));
//	vertices.Add(FVector(0, 100, 0));
//	vertices.Add(FVector(0, 0, 100));
//
//	TArray<int32> Triangles;
//	Triangles.Add(0);
//	Triangles.Add(1);
//	Triangles.Add(2);
//
//	TArray<FVector> normals;
//	normals.Add(FVector(1, 0, 0));
//	normals.Add(FVector(1, 0, 0));
//	normals.Add(FVector(1, 0, 0));
//
//	TArray<FVector2D> UV0;
//	UV0.Add(FVector2D(0, 0));
//	UV0.Add(FVector2D(10, 0));
//	UV0.Add(FVector2D(0, 10));
//
//
//	TArray<FProcMeshTangent> tangents;
//	tangents.Add(FProcMeshTangent(0, 1, 0));
//	tangents.Add(FProcMeshTangent(0, 1, 0));
//	tangents.Add(FProcMeshTangent(0, 1, 0));
//
//	TArray<FLinearColor> vertexColors;
//	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
//	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
//	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
//
//	Mesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
//
//	// Enable collision data
//	Mesh->ContainsPhysicsTriMeshData(true);
//}
void AProceduralMeshActor::CreateFlatSquare()
{


	
	TArray<FVector> Vertices;
	float seed1 = FMath::FRandRange(-50000, 50000);
	float seed2 = FMath::FRandRange(-50000, 50000);
	float seed4 = FMath::FRandRange(-50000,50000);
	float seed3 = FMath::FRandRange(-50000, 50000);

	float YOffset = seed1;
	float YOffset1 = seed2;
	float YOffset2 = seed3;
	float YOffset3 = seed4;
	for (int y{}; y < YWidth; y++)
	{
		float XOffset = seed1;
		float XOffset1 = seed2;
		float XOffset2 = seed3;
		float XOffset3 = seed4;
		for (int x{}; x < XHeight; x++)
		{
			// Here we are creating a Perlin Noise Map, 3 Layers with different seeds. Then setting the input Z to their average
			float Z = FMath::PerlinNoise2D(FVector2D( XOffset, YOffset));
			// Controlling the Perlin Value Somewhat
			float Amp = Amplitude;
			Amp = Amp * Z;
			Z = (Z - 0.01) * Amp;

			float Z1 = FMath::PerlinNoise2D(FVector2D(XOffset1, YOffset1));
			// Controlling the Perlin Value Somewhat
			float Amp1 = Amplitude / 2;
			Amp1 = Amp1 * Z1 ;
			Z1 = (Z1 - 0.01) * Amp1;

			float Z2 = FMath::PerlinNoise2D(FVector2D(XOffset2, YOffset2));
			// Controlling the Perlin Value Somewhat
			float Amp2 = Amplitude / 4;
			Amp2 = Amp2 * Z2;
			Z2 = (Z2 - 0.01) * Amp2;

			float Z3 = FMath::PerlinNoise2D(FVector2D(XOffset3, YOffset3));
			// Controlling the Perlin Value Somewhat
			float Amp3 = Amplitude / 8;
			Amp3 = Amp3 * Z3;
			Z3 = (Z3 - 0.01) * Amp3;

			int input = ((int)Z + (int)Z1 + (int)Z2 + (int)Z3) / 4;
			
			// Water level, want this flat
			if (input < 1100)
			{
				input = 1100;
			}
			int xinc = XIncrement;
			int yinc = YIncrement;
			

	


			Vertices.Add(FVector(0 + (x *xinc), 0 + (y * yinc), input));
			XOffset  += 0.01;
			XOffset1 += 0.02;
			XOffset2 += 0.04;
			XOffset3 += 0.08;
		}
		YOffset  += 0.01;
		YOffset1 += 0.02;
		YOffset2 += 0.04;
		YOffset3 += 0.08;
	}


	TArray<int32> Triangles;

	for (int y{}; y < YWidth - 1; y++)
	{
		for(int x{}; x<XHeight-1;x++)
		{ 
			Triangles.Add(x+(XHeight*y));
			Triangles.Add(x+ XHeight +(YWidth *y));
			Triangles.Add(x + (YWidth * y)+1);
			Triangles.Add(x + (YWidth * y) + 1);
			Triangles.Add(x + XHeight + (YWidth * y));
			Triangles.Add(x + XHeight + (YWidth * y)+1);
		}
		
	}
	
	
	TArray<FVector> Normals;
	for (int y{}; y < YWidth; y++)
	{
		for (int x{}; x < XHeight; x++)
		{
			Normals.Add(FVector(0, 0, 1));
		}
	}

	TArray<FVector2D> UV0;
	for (int y{}; y < YWidth; y++)
	{
		for (int x{}; x < XHeight; x++)
		{ 
		 
			UV0.Add(FVector2D(((float)x/(float)XHeight-1.f)*50.f, ((float)y / (float)YWidth - 1.f) * 50.f));
		}
	}


	TArray<FProcMeshTangent> Tangents;
	for (int y{}; y < YWidth; y++)
	{
		for (int x{}; x < XHeight; x++)
		{
			Tangents.Add(FProcMeshTangent(0, 1, 0));
		}
	}
	
	
	TArray<FLinearColor> VertexColors;
	for (int y{}; y < YWidth; y++)
	{
		for (int x{}; x < XHeight; x++)
		{
			VertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
		}
	}
	
	
	Mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, true);

	// Enable collision data
	Mesh->ContainsPhysicsTriMeshData(true);
	
	
}





