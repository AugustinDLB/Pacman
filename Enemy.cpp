#include "PacmanWindow.h"


Enemy::Enemy(QPixmap EnemyPNG,int x, int y, QGraphicsScene* scene)
	{
		
		//~ QPixmap EnemyPNG("Pacman.PNG");
		EnemyPNG = EnemyPNG.scaled(base, base);
		EnemyImg = scene->addPixmap(EnemyPNG);
		EnemyImg->setPos(x, y);
		timerEnemy = new QTimer(this);
		connect(timer, &QTimer::timeout, this, &Enemy::updateEnemy);
		timerEnemy->start(10);
	}
