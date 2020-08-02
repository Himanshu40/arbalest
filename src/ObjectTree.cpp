/*                    O B J E C T S T R E E V I E W . C P P
 * BRL-CAD
 *
 * Copyright (c) 2018 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 /** @file ObjectTree.cpp
  *
  */

#include <brlcad/Combination.h>
#include "ObjectTree.h"
#include <QStandardItemModel>
#include "MemoryDatabase.h"


void ObjectTree::ObjectTreeCallback::operator()(const BRLCAD::Object& object)
{
	objectId = ++objectTree->lastAllocatedId;
	objectTree->getTree()[objectId] = QVector<int>();
	childrenNames = &objectTree->getTree()[objectId];

	const BRLCAD::Combination* comb = dynamic_cast<const BRLCAD::Combination*>(&object);

	objectTree->getFullNameMap()[objectId] = currentObjectPath;
	if (comb == nullptr)objectTree->getSolidObjectIds().insert(objectId);
	else traverseSubTree(comb->Tree());
}

void ObjectTree::ObjectTreeCallback::traverseSubTree(const BRLCAD::Combination::ConstTreeNode& node) const
{
	switch (node.Operation())
	{
	case BRLCAD::Combination::ConstTreeNode::Union:
	case BRLCAD::Combination::ConstTreeNode::Intersection:
	case BRLCAD::Combination::ConstTreeNode::Subtraction:
	case BRLCAD::Combination::ConstTreeNode::ExclusiveOr:
		traverseSubTree(node.LeftOperand());
		traverseSubTree(node.RightOperand());
		break;

	case BRLCAD::Combination::ConstTreeNode::Not:
		traverseSubTree(node.Operand());
		break;

	case BRLCAD::Combination::ConstTreeNode::Leaf:
		objectTree->getTree()[objectId].append(objectTree->lastAllocatedId + 1);
		QString childName = QString(node.Name());
		objectTree->getNameMap()[objectTree->lastAllocatedId + 1] = childName;
		ObjectTreeCallback callback(objectTree, childName, currentObjectPath);
		objectTree->getDatabase()->Get(node.Name(), callback);
	}
}

ObjectTree::ObjectTree(BRLCAD::MemoryDatabase* database) : database(database) {
	BRLCAD::ConstDatabase::TopObjectIterator it = database->FirstTopObject();

	getTree()[0] = QVector<int>(); // objectId of root is 0
	getNameMap()[0] = "";
	QVector<int>* childrenNames = &getTree()[0];

	while (it.Good()) {
		QString childName = it.Name();
		childrenNames->append(lastAllocatedId + 1);
		getNameMap()[lastAllocatedId + 1] = childName;
		ObjectTreeCallback callback(this, childName, getNameMap()[0]);
		database->Get(it.Name(), callback);
		if (childName != QString("_GLOBAL")) database->Select(it.Name());
		++it;
	}
}

void ObjectTree::traverseSubTree(const int rootOfSubTreeId, void callback(int))
{
	for (int objectId : tree[rootOfSubTreeId]) {
		callback(objectId);
		if (tree.contains(rootOfSubTreeId)) traverseSubTree(objectId, callback);
	}
}

void ObjectTree::rebuildVisibleDisplayListIds()
{
	visibleDisplayListIds.clear();

	for(int objectId : visibleObjectIds)
	{
		visibleDisplayListIds.push_back(objectIdDisplayListIdMap[objectId]);
	}
}

void ObjectTree::changeSubTreeVisibility(const int rootOfSubTreeId, const bool visible)
{
	traverseSubTree(rootOfSubTreeId, [this](int objectId)
	{
		if (drawableObjectIds.contains(objectId))
		visibleObjectIds
	});
}
