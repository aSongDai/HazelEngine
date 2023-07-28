

#include "Hazel.h"

class SandBox : public Hazel::Application
{
public:
	SandBox() = default;
	~SandBox() = default;
};

Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox();
}