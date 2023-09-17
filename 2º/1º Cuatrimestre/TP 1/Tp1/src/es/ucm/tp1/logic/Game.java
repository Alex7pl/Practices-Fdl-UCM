package es.ucm.tp1.logic;

import es.ucm.tp1.control.Level;
import es.ucm.tp1.control.exceptions.InputOutputRecordException;
import es.ucm.tp1.logic.gameobjects.GameObject;

import java.util.Random;

import es.ucm.tp1.logic.gameobjects.Player;
import es.ucm.tp1.utils.StringUtils;


public class Game {
	
	private Long seed;
	
	private Level level;
	
	private Player jugador;
	
	private int cycle;
	
	private Random rand;
	
	private long start;
	
	private long elapsed;
	
	private long finish;
	
	private GameObjectContainer store;
	
	private Record record;
	
	private String thunder;
	
	private static final String FINISH_LINE = "¦";
	
	public Game(Long n, Level N) {
		
		this.seed = n;
		this.level = N;
		
		this.reset(0, null);
	}
	
	public Level getLevel() {
		
		return this.level;
	}
	
	public String getLevelName() {
		
		return level.name();
	}
	
	public int getLevelLength() {
		
		return level.getLength();
	}
	
	public long getRecord() {
		
		return record.getRecord();
	}
	
	public String getThunder() {
		
		return this.thunder;
	}
	
	public int getVisibility() {
		
		return this.level.getVisibility();
	}
	
	public int getRandomWidth() {
		
		return rand.nextInt(level.getWidth());
	}
	
	public int getRandomLane() {
		
		return rand.nextInt(level.getLength() - 1);
	}
	
	public int getRoadWidth() {
		
		return level.getWidth();
	}
	
	public int getPlayerFile() {
		
		return jugador.getX(); 
	}
	
	public int getPlayerCol() {
		
		return jugador.getY();
	}
	
	public boolean isUserExit() {
		
		if(jugador.getVida() == -1) {
			
			return true;
		}
		else return false;
	}
	
	public void exit() {
		
		jugador.exit();
	}
	
	public boolean over() {
		
		if(jugador.getVida() == 0) {
			
			return true;
		}
		else return false;
	}
	
	public void recError() {
		
		jugador.recError();
	}
	
	public boolean isTestMode() {
		
		if(level.name().equals("TEST")) return true;
		else return false;
	}
	
	public void toggleTest() {
		
		reset(this.seed, "TEST");
	}
	
	public boolean isFinished() {
		
		if(this.isUserExit() || this.jugador.getVida() == -2 || this.jugador.getVida() == 0 || this.hasArrived()) return true;
		else return false;
	}
	
	public boolean hasArrived() {
		
		if(jugador.getY() >= level.getLength() - 1) return true;
		else return false;
	}
	
	public String positionToString(int x, int y) {
		
		StringBuilder buffer = new StringBuilder();
		
		if(jugador.isInPosition(x, y)) {
			
			buffer.append(jugador.toString()).append(" ");
		}
		
		if(level.getLength() -1 == y) {
			
			buffer.append(Game.FINISH_LINE);
		}
		
		buffer.append(store.toString(x, y)).append(" ");
		
		return buffer.toString();
	}
	
	public String serialize(int x, int y) {
		
		StringBuilder buffer = new StringBuilder();
		
		if(jugador.isInPosition(x, y)) {
			
			buffer.append(jugador.toString()).append(" (").append(y).append(", ").append(x).append(")").append(StringUtils.LINE_SEPARATOR);
		}
		
		buffer.append(store.serialize(x, y));
		
		return buffer.toString();
	}
	
	public void update(int x, int y) {
		
		if(this.cycle == 0) {
			
			this.start = System.currentTimeMillis();
		}
		
		jugador.doCollision(this.store);
		
		jugador.update(x, y);
		
		jugador.doCollision(this.store);
		
		store.update();
		
		GameObjectGenerator.generateRuntimeObjects(this);
		
		this.cycle++;
		
		store.removeDead();
	}
	
	public int goUp() {
		
		int x = 0;
		
		if(jugador.getX() == 0) x = jugador.getX();
		
		else x = jugador.getX() - 1;
		
		return x;
	}
	
	public int go() {
		
		int x;
		
		x = jugador.getX();
		
		return x;
	}
	
	public int goDown() {
		
		int x = 0;
		
		if(jugador.getX() == level.getWidth() - 1) x = jugador.getX();
		
		else x = jugador.getX() + 1;
		
		return x;
	}
	
	public int playerCoins() {
		
		return jugador.playerCoins();
	}
	
	public void moreCoins(int coins) {
		
		jugador.moreCoins(coins);
	}
	
	public void execute(InstantAction action) {
		
		action.execute(this);
	}
	
	public void shoot(int x, int y) {
		
		int i = 0;
		
		int j = y + level.getVisibility();
		
		boolean shoot = false;
		
		while(i < j && !shoot) {
			
			shoot = store.shoot(x, y);
			i++;
			y++;
		}
	}
	
	public void explosion(int x, int y) {
		
		if(x != 0) {
			
			store.doExplosion(x - 1, y - 1);
			store.doExplosion(x - 1, y);
			store.doExplosion(x - 1, y + 1);
		}
		
		if(x != level.getVisibility() - 1) {
			
			store.doExplosion(x + 1, y - 1);
			store.doExplosion(x + 1, y);
			store.doExplosion(x + 1, y + 1);
		}
		
			store.doExplosion(x, y - 1);
			store.doExplosion(x, y + 1);
			store.doExplosion(x, y);
	}
	
	public void thunder() {
		
		StringBuilder buffer = new StringBuilder("Thunder hit position: (");
		
		int x = this.getRandomWidth();
		int y = rand.nextInt(getVisibility() - 1) + this.getPlayerCol();
		
		buffer.append(y - getPlayerCol()).append(" , ").append(x).append(")").append(store.thunder(x, y));
		
		this.thunder = buffer.toString();
		
	}
	
	public void wave() {
		
		store.wave(jugador.getY(), jugador.getY() + level.getVisibility() - 1, level.getWidth());
	}
	
	public void cheat(int id) {
		
		store.cheat(level.getWidth(), jugador.getY() + level.getVisibility() - 1);
		
		GameObjectGenerator.forceAdvanceObject(this, id, jugador.getY() + level.getVisibility() - 1);
	}
	
	public void clear() {
		
		store.clear();
	}
	
	public int getCycle() {
		
		return this.cycle;
	}
	
	public int distanceToGoal() {
		
		return level.getLength() - jugador.getY();
	}
	
	public long elapsed() {
		
		this.finish = System.currentTimeMillis();
		
		if(this.cycle == 0) return this.start;
		else { 
			
			this.elapsed = this.elapsed + (this.finish - this.start);
			
			this.start = this.finish;
			return elapsed;
		}
	}
	
	public void reset(long s, String l) {
		
		this.store = new GameObjectContainer();
		
		if(s != 0) {
			
			this.seed = s;
			this.level = Level.valueOfIgnoreCase(l);
		}
		this.record = new Record();
		this.rand = new Random(seed);
		this.jugador = new Player(level);
		this.thunder = "";
		this.cycle = 0;
		this.start = 0;
		this.elapsed = 0;
		
		
		try {
			record.load(this);
		} catch (InputOutputRecordException e) {
			
			System.out.println(e.getMessage());
			this.recError();
		}
	
		
		GameObjectGenerator.reset(this.level);
		
		GameObjectGenerator.generateGameObjects(this, this.level);
		
	}
	
	public void tryToAddObject(GameObject o, double frequency) {
		if (rand.nextDouble() < frequency) {
			if (this.store.isPositionEmpty(o.getX(), o.getY())) {
				this.store.addObject(o);
			}
		}
	}
	
	public void forceAddObject(GameObject o) {
		
		this.store.addObject(o);
	}

	public boolean isNewRecord() {
		
		if(this.record.getRecord() > this.elapsed) return true;
		else return false;
	}
	
	public void save() {
		
		try {
			
			record.save(this);
		}
		catch(InputOutputRecordException e) {
			
			System.out.println(e.getMessage());
			
		}
	}
	
	
	
}
	
	
	
