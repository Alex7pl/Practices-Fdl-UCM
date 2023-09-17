package es.ucm.tp1.logic;

import es.ucm.tp1.logic.gameobjects.Player;

public interface Collider {

	void receiveCollision(Player player);
	
	boolean receiveShoot();
	
	void receiveExplosion();

}
