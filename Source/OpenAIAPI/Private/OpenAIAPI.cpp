// Copyright Epic Games, Inc. All Rights Reserved.

#include "OpenAIAPI.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "OpenAIUtils.h"

#define LOCTEXT_NAMESPACE "FOpenAIAPIModule"

TMap<FString, FString> FOpenAIAPIModule::LoadConfigFile() {
  UE_LOG(LogTemp, Warning, TEXT("LoadConfigFile"));
  FString ConfigFilePath = FPaths::ProjectDir() / TEXT(".ini");
  FString ConfigFileContents;
  FFileHelper::LoadFileToString(ConfigFileContents, *ConfigFilePath);

  TArray<FString> ConfigLines;
  ConfigFileContents.ParseIntoArrayLines(ConfigLines);
  TMap<FString, FString> config;
  for (const FString &ConfigLine : ConfigLines) {
    TArray<FString> ConfigPair;
    ConfigLine.ParseIntoArray(ConfigPair, TEXT("="), true);

    if (ConfigPair.Num() == 2) {
      FString ConfigKey = ConfigPair[0];
      FString ConfigValue = ConfigPair[1];
      UE_LOG(LogTemp, Warning, TEXT("%s=%s"), *ConfigKey, *ConfigValue);
      config.Add(ConfigKey, ConfigValue);
    }
  }
  return config;
}

void FOpenAIAPIModule::StartupModule() {
  auto map = LoadConfigFile();
  if (this->_useApiKeyFromEnvVariable) {
    this->_apiKey = map[FString("OPENAI_API_KEY")];
  }
  FString apiKey = UOpenAIUtils::getApiKey();
  UE_LOG(LogTemp, Warning, TEXT("APIKEY %s"), *apiKey);
  // This code will execute after your module is loaded into memory; the exact
  // timing is specified in the .uplugin file per-module
}

void FOpenAIAPIModule::ShutdownModule() {
  // This function may be called during shutdown to clean up your module.  For
  // modules that support dynamic reloading, we call this function before
  // unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FOpenAIAPIModule, OpenAIAPI)