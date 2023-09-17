package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.control.Level;
import es.ucm.tp1.logic.GameObjectContainer;

public class Player {
	
	private int x;
	
	private int y;
	
	private int vida;
	
	private int monedas;
	
	private static final String symbolA = ">";
	
	private static final String symbolM = "@";
	
	
	
	public Player(Level level) {
		
		this.vida = 1;
		this.monedas = 0;
		
		if(level.name().equals("HARD"))
		this.x = 2;
		else 
		this.x = 1;
		this.y = 0;
	}
	
	public int getVida() {
		
		return this.vida;
	}
	
	public int getY() {
		
		return this.y;
	}
	
	public int getX() {
		
		return this.x;
	}
	

	public String toString() {
		
		if(vida == 1) {
			
			return symbolA;
		}
		else {
			
			return symbolM;
		}
	}
	
	public void exit() {
		
		this.vida = -1;
	}
	
	public void recError() {
		
		this.vida = -2;
	}
	
	public void crash() {
		
		this.vida = 0;
	}
	
	public boolean isInPosition(int x, int y) {
		
		boolean is = false;
		
		if (this.x == x && this.y == y) is = true;
		
		return is;
	}
	
	public boolean doCollision(GameObjectContainer store) {
		
		int other = store.getObjectInPos(this.x, this.y);
		
		if (other != -1) {
		return store.receiveCollision(this, other);
		}
		return false;
	
	}
	
	public int playerCoins() {
		
		return this.monedas;
	}
	
	public void moreCoins(int money) {
		
		this.monedas = this.monedas + money;
	}
	
	public void update(int x, int y) {
		
		this.x = x;
		this.y = y;
	}

}
