package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Collider;
import es.ucm.tp1.logic.Game;

public abstract class GameObject implements Collider {

	protected int x, y;

	protected Game game;

	public GameObject(Game game, int x, int y) {
		this.x = x;
		this.y = y;
		this.game = game;
	}

	public boolean isInPosition(int x, int y) {
		return this.x == x && this.y == y;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}
	
	public void wave() {
		
		y++;
	}

	public abstract boolean isAlive();
		
	public abstract void onEnter();

	public abstract void update();

	public abstract void onDelete();
	
	public abstract String serialize();


	// TODO add your code

}
