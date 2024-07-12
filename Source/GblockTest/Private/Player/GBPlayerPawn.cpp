// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GBPlayerPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h" 
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AGBPlayerPawn::AGBPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent,USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	
}

// Called when the game starts or when spawned
void AGBPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
  
	if (const ULocalPlayer* LocalPlayer = this->GetWorld()->GetFirstLocalPlayerFromController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(CamMappingContext, 0); 
		}
	} 
}

// Called every frame
void AGBPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGBPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{ 
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGBPlayerPawn::Move);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ThisClass::Zoom); 
	} 
	else
	{
		//UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}

}
 
void AGBPlayerPawn::Move(const FInputActionValue& Value)
{
	//Input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	//Add movement as per world's forward & right vector
	AddMovementInput(FVector::ForwardVector, MovementVector.Y);
	AddMovementInput(FVector::RightVector, MovementVector.X);
}
 
void AGBPlayerPawn::Zoom(const FInputActionValue& Value)
{
	SpringArmComponent->TargetArmLength += Value.Get<float>();
}
