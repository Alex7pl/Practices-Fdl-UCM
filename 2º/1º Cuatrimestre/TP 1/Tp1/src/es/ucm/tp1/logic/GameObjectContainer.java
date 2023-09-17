package es.ucm.tp1.logic;

import es.ucm.tp1.logic.gameobjects.GameObject;
import es.ucm.tp1.logic.gameobjects.Player;

import java.util.*;

public class GameObjectContainer {
	
	private List<GameObject> gameobjects;
	
	public GameObjectContainer() {
		gameobjects = new ArrayList<>();
	}
	
	public void addObject(GameObject object) {
		
		gameobjects.add(object);
		gameobjects.get(gameobjects.size() - 1).onEnter();
	}
	
	public void eliminateObject(int object) {
		
		gameobjects.get(object).onDelete();
		gameobjects.remove(object);
	}
	
	public boolean isPositionEmpty(int x, int y) {
		
		boolean empty = true;
		
		int i = 0;
		
		while(i < this.gameobjects.size() && empty == true) {
			
			
			if(gameobjects.get(i).isInPosition(x, y)) empty = false;
			
			else i++;
		}
		
		return empty;
	}
	
	public int getObjectInPos(int x, int y) {
		
		int object = 0;
		
		boolean encontrado = false;
		
		while(object < gameobjects.size() && encontrado == false) {
			
			if(gameobjects.get(object).isInPosition(x, y)) {
				
				encontrado = true;
			}
			else object++;
		}
		
		if(encontrado == false) object = -1;
		
		return object;
	}
	
	public boolean receiveCollision(Player player, int object) {
		
		gameobjects.get(object).receiveCollision(player);
		
		return true;
	}
	
	public void removeDead() {
		
		for(int i = 0; i < gameobjects.size(); i++) {
			
			if(!gameobjects.get(i).isAlive()) {
				
				this.eliminateObject(i);
			}
		}
	}
	
	public boolean shoot(int x, int y) {
		
		int object = 0;
		
		boolean encontrado = false;
		boolean shoot = false;
		
		while(object < gameobjects.size() && shoot == false) {
			
			if(gameobjects.get(object).isInPosition(x, y)) {
				
				if(gameobjects.get(object).receiveShoot())
				encontrado = true;
				shoot = true;
			}
			else object++;
		}
		
		return encontrado;
		
	}
	
	public void doExplosion(int x, int y) {
		
		int i = this.getObjectInPos(x, y);
		
		if(i != -1) {
			
			gameobjects.get(i).receiveExplosion();
		}
	}
	
	public String thunder(int x, int y) {
		
		String thunder = "";
		
		int object = this.getObjectInPos(x, y);
		
		if(object != -1) {
			
			thunder = " -> " + gameobjects.get(object).toString() + " hit";
			this.eliminateObject(object);
		}
		
		return thunder;
	}
	
	public void wave(int x, int y, int z) {
		
		for (int i = 0; i < z; i++) {
			for (int j = y; j > x; j--) {
				
				int object = this.getObjectInPos(i, j);
				if(object != -1 && this.getObjectInPos(i, j + 1) == -1) gameobjects.get(object).wave();
			}
		}
	}
	
	public void cheat(int x, int y) {
		
		for(int i = 0; i < x; i++) {
			
			int object = this.getObjectInPos(i, y);
			if(object != -1) this.eliminateObject(object);
		}
	}
	
	public void clear() {
		
		for(int i = 0; i < gameobjects.size(); i++) {
			
			gameobjects.get(i).onDelete();
		}
		
		gameobjects.clear();
	}
	
	public void update() {
		
		for(int i = 0; i < gameobjects.size(); i++) {
			
			gameobjects.get(i).update();
		}
	}
	
	public String serialize(int x, int y) {
		
		StringBuilder buffer = new StringBuilder();
		
		boolean empty = true;
		
		for(int i = 0; i < gameobjects.size(); i++) {
			
			if(gameobjects.get(i).isInPosition(x, y)) { 
				
				if(gameobjects.get(i).isAlive()) {
					buffer.append(gameobjects.get(i).serialize());
					empty = false;
				}
			}
		}
		
		if(empty) buffer.append("");
		
		return buffer.toString();
	}

	public String toString(int x, int y) {
		
		StringBuilder buffer = new StringBuilder();
		
		boolean empty = true;
		
		for(int i = 0; i < gameobjects.size(); i++) {
			
			if(gameobjects.get(i).isInPosition(x, y)) { 
				
				if(gameobjects.get(i).isAlive()) {
					buffer.append(gameobjects.get(i).toString()).append(" ");
					empty = false;
				}
			}
		}
		
		if(empty) buffer.append(" ");
		
		return buffer.toString();
	}
	
	
}
