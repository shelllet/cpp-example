#include "common.hpp"
#include <libzippp/libzippp.h>
#include <QVBoxLayout>
#include <QStringListModel>
#include <QLineEdit>
#include <QComboBox>
#include "variable_table_component.h"
#include "common/variable.h"

namespace {
	using namespace libzippp;
	using namespace shelllet::creator;
	using namespace YAML;
}

VariableTableComponent::ComboBoxItemDelegate::ComboBoxItemDelegate(QObject* parent /*= nullptr*/)
	: QItemDelegate(parent)
{
}

QWidget* VariableTableComponent::ComboBoxItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	auto* comboBox = new QComboBox(parent);
	QStringListModel* model = new QStringListModel({ "Auto", "String", "Object" }, comboBox);
	comboBox->setModel(model);
	return comboBox;
}
VariableTableComponent::VariableTableComponent(QWidget* parent)
	: QWidget(parent)
	, tableView_(new QTableView)
	, toolbar_(new QToolBar())
{
	setLayout(new QVBoxLayout);
	layout()->setContentsMargins({ 0, 0, 0, 0 });

	toolbar_->addAction(tr("new"), this, SLOT(addRow()));
	toolbar_->addAction(tr("del"), this, SLOT(removeRow()));
	toolbar_->addWidget(new QLineEdit());

	layout()->addWidget(toolbar_);
	layout()->addWidget(tableView_);

	tableView_->setItemDelegateForColumn(Columns::Type, new ComboBoxItemDelegate(this));
}

VariableTableComponent::~VariableTableComponent()
{
	//guard.reset();
	//thread.join();
}

void VariableTableComponent::create()
{
	//db->exec("DOROP TABLE IF EXISTS variables");
	//db->exec("CREATE TABLE variables (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, type TEXT,  value TEXT, ref INTEGER, desc TEXT)");
}

void VariableTableComponent::load(const Path& /*filename*/)
{
	auto file = Environment::getInstance()->getCurrentProjectPath() / Environment::getInstance()->getOptions()->config_filename.toStdString();
	YAML::Node config;
	try
	{
		config = YAML::LoadFile(file.toString().toStdString());



	}
	catch (const YAML::ParserException& e)
	{
		LOG_WARNING("rpa") << e.msg << std::endl;
	}

	Node variables;
	if (config)
		variables = config["variables"];

	model_ = new model::VariableModel(variables, this);
	tableView_->setModel(model_);
}

void VariableTableComponent::save(const Path& /*filename*/)
{

	auto file = Environment::getInstance()->getCurrentProjectPath()
		/ Environment::getInstance()->getOptions()->config_filename.toUtf8().constData();

	YAML::Node config = YAML::LoadFile(file.toString().toStdString());

	config["variables"] = model_->node();
	std::string yaml;
	std::ofstream stream(yaml);
	stream << config;


	File ss(file);

	ss.write(yaml.c_str());

}

void VariableTableComponent::addRow()
{
	model_->insertRows(model_->rowCount(), 1);
}

void VariableTableComponent::removeRow()
{
	auto s = tableView_->selectionModel()->selectedRows();

	model_->removeRows(s.cbegin()->row(), s.count());
}