#include "app/src/input_processor/command_processor/command_processor.h"

class engine;

class roots_processor : public command_processor
{
public:
  explicit roots_processor(engine& engine);

  void execute(const std::string&) override;

  [[nodiscard]] std::string get_description() const override;

private:
  engine& m_engine;

  static constexpr auto description = "Use 'roots' to get all indexed roots.";
};
