#pragma once

class KSUtils
{
public:
    template<typename T>
    static T* GetKSPlayerComponent(APawn* PlayerPawn)
    {
        if(!PlayerPawn)
            return nullptr;
    
        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }
};