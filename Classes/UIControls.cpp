#include "UIControls.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#pragma execution_character_set("utf-8")
#endif

void Inventory::update(float dt)
{
	if (focusGrid)
		showDetails(focusGrid);
}

Inventory* Inventory::create(const std::string& name)
{
	Inventory *sprite = new (std::nothrow) Inventory();
	if (sprite && sprite->initWithFile(name) && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Inventory::init()//智能控件的话， 要引用一个东西（有物体的指针），当东西为nullptr时自动变为grid
{
	focusGrid = nullptr;
	//物品说明
	label = Label::createWithTTF("物品说明", "fonts/SIMYOU.TTF", 12);
	label->setAnchorPoint(Vec2(0.5, 0.5));
	label->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height * 0.25));
	
	label->setDimensions(this->getContentSize().width, this->getContentSize().height * 0.25);
	//label->setColor(Color3B::RED);
	this->addChild(label);
	//RichText::create();
	//物品栏
	isTouched = false;
	auto grid_a = Sprite::create("grid.png");
	auto grid_b = Sprite::create("grid.png");
	auto grid_c = Sprite::create("grid.png");
	auto grid_d = Sprite::create("grid.png");
	auto grid_e = Sprite::create("grid.png");
	auto grid_f = Sprite::create("grid.png");

	grid_a->setName("grid.png");
	grid_b->setName("grid.png");
	grid_c->setName("grid.png");
	grid_d->setName("grid.png");
	grid_e->setName("grid.png");
	grid_f->setName("grid.png");

	grid_a->setUserData("null");
	grid_b->setUserData("null");
	grid_c->setUserData("null");
	grid_d->setUserData("null");
	grid_e->setUserData("null");
	grid_f->setUserData("null");
	

	 a = grid::create(grid_a, grid_a, [this](Ref *pSender) {
		/*if (a->isEmpty){
			label->setString("空");
		}else{
			label->setString(a->description);
		}
		printDialog();
		clearLabel(a);*/
		 focusGrid = a;
		 showDetails(a);
	});
	 b = grid::create(grid_b, Node::create(), [this](Ref *pSender) {
		 /*if (b->isEmpty){
			 label->setString("空");
		 }else{
			 label->setString(b->description);
		 }
		 printDialog();
		 clearLabel(b);*/
		 showDetails(b);
		 focusGrid = b;
	 });
	 c = grid::create(grid_c, Node::create(), [this](Ref *pSender) {
		 /*if (c->isEmpty){
			 label->setString("空");
		 }else{
			 label->setString(c->description);
		 }
		 printDialog();
		 clearLabel(c);*/
		 showDetails(c);
		 focusGrid = c;
	 });
	 d = grid::create(grid_d, Node::create(), [this](Ref *pSender) {
		 /*if (d->isEmpty){
			 label->setString("空");
		 }else{
			 label->setString(d->description);
		 }
		 printDialog();
		 clearLabel(d);*/
		 showDetails(d);
		 focusGrid = d;
	 });
	 e = grid::create(grid_e, Node::create(), [this](Ref *pSender) {
		 /*if (e->isEmpty){
			 label->setString("空");
		 }else{
			 label->setString(e->description);
		 }
		 printDialog();
		 clearLabel(e);*/
		 showDetails(e);
		 focusGrid = e;
	 });
	 f = grid::create(grid_f, Node::create(), [this](Ref *pSender) {
		 /*if (f->isEmpty){
			 label->setString("空");
		 }else{
			 label->setString(f->description);
		 }
		 printDialog();
		 clearLabel(f);*/
		 showDetails(f);
		 focusGrid = f;
	 });
	 a->scheduleString = "aa";
	 b->scheduleString = "bb";
	 c->scheduleString = "cc";
	 d->scheduleString = "dd";
	 e->scheduleString = "ee";
	 f->scheduleString = "ff";

	grids.pushBack(a);
	grids.pushBack(b);
	grids.pushBack(c);
	grids.pushBack(d);
	grids.pushBack(e);
	grids.pushBack(f);

	itemsMenu = Menu::create(a, b, c, d, e, f, NULL);
	itemsMenu->setContentSize(Size(this->getContentSize().width, this->getContentSize().height * 0.75));
	itemsMenu->alignItemsInColumns(3, 3, NULL);
	//itemsMenu->alignItemsInRows(2, 2, 2, NULL);
	itemsMenu->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height - itemsMenu->getContentSize().height / 2));
	this->addChild(itemsMenu);

	//scheduleUpdate();
	return true;
}

void Inventory::addItem(Sprite** sprite)
{
	for (auto &i : grids)
	{
		if (i->isEmpty)
		{
			//i->isEmpty = false;
			i->addImage(sprite);
			//label->setString(*(std::string *)i->getNormalImage()->getUserData());
			//showDetails(i->getNormalImage());
			//i->scheduleUpdate();
			break;
		}
	}
}

void Inventory::addItem(Props* p)
{
	for (auto &i : grids)
	{
		if (!i->isEmpty && i->p->file == p->file)
		{
			i->getNormalImage()->runAction(Sequence::create(ScaleTo::create(0.25f, 1.25f), RotateBy::create(0.5f, 360), ScaleTo::create(0.25f, 1.0f), NULL));
			return;
		}
	}
	for (auto &i : grids)
	{
		/*if (i->p->file == p->file)
		{
			break;
		}*/
		if (i->isEmpty)
		{
			i->addImage(p);
			showDetails(i);
			focusGrid = i;
			//p->setPosition(Point::ZERO);//累死我了，终于发现。2019-9-5 morning
			//i->isEmpty = false;
			//i->setNormalImage(p);
			//i->setName(p->getName());
			//i->description = p->getDescription();
			////自动显示
			//label->setString(i->description);
			//printDialog();
			//clearLabel(i);
			break;
		}
	}
}

void Inventory::removeItem(const std::string& name, bool removeAll)
{
	if (!removeAll)
	{
		for (auto &i : grids)
		{
			if (i->getName() == name)
			{
				i->setName("");
				i->isEmpty = true;
				i->setNormalImage(Sprite::create("grid.png"));
				break;
			}
		}
	}
	else
	{
		for (auto &i : grids)
		{
			if (i->getName() == name)
			{
				i->setName("");
				i->isEmpty = true;
				i->setNormalImage(Sprite::create("grid.png"));
			}
		}
	}
}

void Inventory::showDetails(grid* g)
{
	std::string details;
	if (g->isEmpty)
	{
		details = "null";
	}
	else
	{	
		details = g->p->getDescription();
	}
	label->setString(details);

	int index = 0;
	while (label->getLetter(index) != nullptr)
	{
		label->getLetter(index)->stopAllActions();
		label->getLetter(index)->setVisible(false);
		index++;
	}

	index = 0;
	while (label->getLetter(index) != nullptr)
	{
		label->getLetter(index)->runAction(
			Sequence::create(
				DelayTime::create(index * 0.1f),
				Show::create(), nullptr)
		);
		index++;
	}
}

void Inventory::showDetails(Node* image)
{
	auto details = *(std::string *)image->getUserData();
	label->setString(details);

	int index = 0;
	while (label->getLetter(index) != nullptr)
	{
		//label->getLetter(index)->stopAllActions();//清除前面的printDialog
		label->getLetter(index)->setVisible(false);
		index++;
	}

	index = 0;
	while (label->getLetter(index) != nullptr)
	{
		label->getLetter(index)->runAction(
			Sequence::create(
				DelayTime::create(index * 0.1f),
				Show::create(), nullptr)
		);
		index++;
	}
}

void Inventory::printDialog()
{
	int index = 0;
	while (label->getLetter(index) != nullptr)
	{
		label->getLetter(index)->stopAllActions();//清除前面的printDialog
		label->getLetter(index)->setVisible(false);
		index++;
	}
	
	index = 0;
	while (label->getLetter(index) != nullptr)
	{
		label->getLetter(index)->runAction(
			Sequence::create(
				DelayTime::create(index * 0.1f),
				Show::create(), nullptr)
		);
		index++;
	}
}

void Inventory::clearLabel(grid* g)
{
	auto a = grids;
	a.eraseObject(g);
	for (auto &i : grids)
	{
		unschedule(i->scheduleString);
	}
	schedule([this, g](float dt) {
		if (g->isEmpty) {
			label->setString("空");
		}
	}, 0.0f, g->scheduleString);
}



PlayerHP* PlayerHP::create(const std::string& name, const std::string& source)
{
	PlayerHP *sprite = new (std::nothrow) PlayerHP();
	if (sprite && sprite->initWithFile(name) && sprite->init(source))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool PlayerHP::init(const std::string& source)
{
	isTouched = false;
	m_bg = Sprite::create(source);
	m_bg->setOpacity(20);
	m_bg->setPosition(this->getContentSize().width / 2, this->getContentSize().height * 2/3);
	addChild(m_bg);

	auto blood = Sprite::create(source);
	blood->setColor(Color3B::YELLOW);
	m_progressBar = ProgressTimer::create(blood);
	m_progressBar->setType(ProgressTimer::Type::BAR);//设置进程条的类型
	m_progressBar->setBarChangeRate(Point(0, 1));//
	m_progressBar->setMidpoint(Point(0, 0));//设置进度的运动方向
	m_progressBar->setPosition(this->getContentSize().width / 2, this->getContentSize().height * 2/3);
	addChild(m_progressBar);

	description = "PlayerHP";
	m_label = Label::createWithTTF(description, "fonts/SIMYOU.TTF", 12);
	m_label->setPosition(this->getContentSize().width / 2, this->getContentSize().height * 1/4);
	addChild(m_label);

	//listenScaling();
	return true;
}

void PlayerHP::listenScaling()
{
	m_mouseEventListener = EventListenerMouse::create();
	m_mouseEventListener->onMouseScroll = [this](EventMouse* event) {
		if (this->getBoundingBox().containsPoint(event->getLocationInView())) {
			if (event->getScrollY() > 0) {
				if (this->getScale() * 0.8 >= 0.25f) {
					this->setScale(this->getScale() * 0.8f);
				}
			}else {
				this->setScale(this->getScale() * 1.25f);
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_mouseEventListener, this);
}
