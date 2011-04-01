#include "IsisDebug.h"

#include "PointModel.h"

#include <QString>

#include "ControlNet.h"
#include "ControlPoint.h"

#include "PointParentItem.h"
#include "MeasureLeafItem.h"


namespace Isis
{
  PointModel::PointModel(ControlNet * controlNet, QString name, QTreeView * tv,
      QObject * parent) : TreeModel(controlNet, name, tv, parent)
  {
    rebuildItems();
  }


  PointModel::~PointModel()
  {
  }


  void PointModel::rebuildItems()
  {
    clearParentItems();

    beginInsertRows(QModelIndex(), 0, cNet->GetNumPoints() - 1);
    for (int i = 0; i < cNet->GetNumPoints(); i++)
    {
      ControlPoint * point = cNet->GetPoint(i);
      PointParentItem * pointItem = new PointParentItem(point);
      parentItems->append(pointItem);
      for (int j = 0; j < point->GetNumMeasures(); j++)
      {
        ControlMeasure * measure = point->GetMeasure(j);
        ASSERT(measure);
        MeasureLeafItem * measureItem = new MeasureLeafItem(measure, pointItem);
        pointItem->addChild(measureItem);
      }
    }
    endInsertRows();
  }
}
