#include "DummyStorable.hpp"
#include "database/Data.hpp"
#include "database/utils.hpp"

#include <range/v3/all.hpp>

#include <sstream>
#include <unordered_map>

DummyStorable::DummyStorable(int id) : id_{id} {}

DummyStorable::DummyStorable(int id, std::string name)
    : id_{id}, name_{std::move(name)}
{}

DummyStorable::DummyStorable(
    std::vector<database::ColumnProperties> const &schema,
    database::Row const &data)
{
  this->set_data(schema, data);
}

auto DummyStorable::id() const -> int
{
  return this->id_;
}

auto DummyStorable::name() const -> std::string const
{
  return this->name_;
}

void DummyStorable::set_name(std::string_view name)
{
  this->name_ = name;
  database::utils::update(*this);
}

auto DummyStorable::get_data() const -> database::Data const
{
  database::Data data;
  data.table_name = "DummyStorable";

  // DummyStorable ID|name
  size_t num_columns = 2;
  data.schema.reserve(num_columns);

  // The properties of a single column;
  database::ColumnProperties column_properties;

  // DummyStorable_id column begin
  column_properties.name = data.table_name + "_id";
  column_properties.data_type = database::DataType::INTEGER;
  column_properties.constraint = database::Constraint::PRIMARY_KEY;
  data.schema.emplace_back(column_properties);

  std::vector<database::Row::row_data_t> new_row;
  new_row.reserve(num_columns);

  // std::variant to hold multiple data types. Defined in Data.hpp.
  database::Row::row_data_t row_data = this->id();
  new_row.emplace_back(row_data);

  // name column Begin
  // The name of the table needs to be in single quotes for the SQL command
  column_properties.name = "name";
  column_properties.data_type = database::DataType::TEXT;

  // The rest of the columns from hereon will be NOT NULL constraint
  column_properties.constraint = database::Constraint::NOT_NULL;
  data.schema.emplace_back(column_properties);

  std::stringstream quoted_name;
  quoted_name << "'" << this->name() << "'";
  row_data = quoted_name.str();
  new_row.emplace_back(row_data);

  data.rows.emplace_back(database::Row{new_row});

  return data;
}

void DummyStorable::set_data(
    std::vector<database::ColumnProperties> const &schema,
    database::Row const &row)
{
  std::unordered_map<std::string_view, database::Row::row_data_t>
      organized_data;

  auto data = row.row_data;
  for (auto const &[first, second] : ranges::view::zip(schema, data)) {
    organized_data[first.name] = second;
  }

  this->id_ = std::get<int>(organized_data["DummyStorable_id"]);

  this->name_ = std::get<std::string>(organized_data["name"]);
}

auto DummyStorable::str() const -> std::string
{
  std::stringstream ss;
  ss << this->id();

  auto const delimeter = "|";
  ss << delimeter << this->name();

  return ss.str();
}
