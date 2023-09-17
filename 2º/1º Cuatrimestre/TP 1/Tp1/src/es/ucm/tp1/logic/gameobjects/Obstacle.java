package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.utils.StringUtils;

public class Obstacle extends GameObject{
	
	private static final String symbol = "░";
	
	public static final String INFO = "[Obstacle] hits car";
	
	private boolean vida;
	
	private static int obstacleCount;
	
	
	public Obstacle(Game game, int x, int y) {
		
		super(game, x, y);
	}
	
	public String toString() {
		
		return symbol;
	}
	
	public String serialize() {
		StringBuilder str = new StringBuilder();
		
		str.append(this.toString()).append(" (").append(y).append(", ").append(x).append(")").append(StringUtils.LINE_SEPARATOR);
		
		return str.toString();
	}
	
	public static void reset() {
		
		obstacleCount = 0;
	}
	
	public static int getObstaclesCount() {
		
		return obstacleCount;
	}

	@Override
	public void receiveCollision(Player player) {
		
		if(vida) {
		
			this.vida = false;
			player.crash();
		}

	}


	@Override
	public boolean isAlive() {
		
		return this.vida;
	}


	@Override
	public void onEnter() {
		
		this.vida = true;
		obstacleCount = obstacleCount + 1;
		
	}


	@Override
	public void update() {
		// TODO Auto-generated method stub
		
	}


	@Override
	public void onDelete() {
		
		obstacleCount--;
	}

	@Override
	public boolean receiveShoot() {
		
		this.vida = false;
		return true;
	}

	@Override
	public void receiveExplosion() {
		
		this.receiveShoot();
	}
	
}
