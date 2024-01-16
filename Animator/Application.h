#pragma once

class Application
{
public:
    inline Application() { };
    inline virtual ~Application() { };
    inline virtual void Initialize() {};
    inline virtual void Update(float DeltaTime) {};
    inline virtual void Render(float AspectRatio) {};
    inline virtual void Shutdown() {};
private:
    Application(const Application&);
    Application& operator=(const Application&);
};

