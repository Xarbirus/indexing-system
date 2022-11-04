#pragma once

class service;

class engine
{
public:
  explicit engine(service& service);

  void stop_service();

private:
  service& m_service;
};
