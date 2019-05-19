#pragma once

#include "database/Storable.hpp"
#include "database/utils.hpp"

#include <soci.h>

#include <string>
#include <string_view>

class DummyStorable : public database::Storable {
public:
  DummyStorable(DummyStorable &&f) = default;
  DummyStorable &operator=(DummyStorable const &f) = default;
  DummyStorable &operator=(DummyStorable &&f) = default;
  ~DummyStorable() override = default;

  auto get_data() const -> database::Data const override;
  auto id() const -> int override;
  auto name() const -> std::string const override;
  auto str() const -> std::string override;

  void set_name(std::string_view name) override;

  struct Allocator : std::allocator<DummyStorable> {
    template <class DummyStorable, typename... Args>
    void construct(DummyStorable *buffer, Args &&... args)
    {
      /**
       * @brief In place new construction of storable by memory pool that is
       *        given
       */
      new (buffer) DummyStorable(std::forward<Args>(args)...);
    }

    template <class DummyStorable> struct rebind {
      using other = Allocator;
    };
  };

  friend struct Allocator;

private:
  explicit DummyStorable(int id);

  DummyStorable() = default;
  DummyStorable(DummyStorable const &f) = default;
  DummyStorable(int id, std::string name);
  DummyStorable(std::vector<database::ColumnProperties> const &schema,
                database::Row const &data);

  void set_data(std::vector<database::ColumnProperties> const &schema,
                database::Row const &data) override;

  int id_;
  std::string name_;
};
