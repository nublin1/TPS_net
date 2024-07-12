// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/IHealthInterface.h"

IIHealthInterface::IIHealthInterface(): Health(100), MaxHealth(100)
{
}

// Add default functionality here for any IIHealthInterface functions that are not pure virtual.
IIHealthInterface::IIHealthInterface(float Health, float MaxHealth): Health(Health),
                                                                     MaxHealth(MaxHealth)
{
}
