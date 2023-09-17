package es.ucm.tp1.control.commands;

import es.ucm.tp1.control.Buyable;
import es.ucm.tp1.control.exceptions.CommandExecuteException;
import es.ucm.tp1.control.exceptions.CommandParseException;
import es.ucm.tp1.control.exceptions.InvalidPositionException;
import es.ucm.tp1.control.exceptions.NotEnoughCoinsException;
import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.gameobjects.Grenade;

public class GrenadeCommand extends Command implements Buyable{
	
	private static final String NAME = "grenade";

	private static final String DETAILS = "[g]renade <x> <y>";

	private static final String SHORTCUT = "g";

	private static final String HELP = "add a grenade in position x, y";

	private static final String FAILED_MSG = "Failed to add grenade";

	public GrenadeCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) throws CommandExecuteException{
		
		try {
			
			this.coords(game.getRoadWidth());
		}
		catch(InvalidPositionException e) {
			
			System.out.println(e.getMessage());
			throw new CommandExecuteException(String.format("[ERROR]: %s", FAILED_MSG), e);
		}
		
		try {
				
				
			this.buy(game);
				
				
			game.moreCoins(-this.cost());
				
			game.forceAddObject(new Grenade(game, this.x, this.y + game.getPlayerCol()));
				
			game.update(game.go(), game.getPlayerCol());
			
			
		}
			
		catch(NotEnoughCoinsException e){
				
				
			System.out.println(e.getMessage());
				
			throw new CommandExecuteException(String.format("[ERROR]: %s", FAILED_MSG), e);
			
		}
		
		return true;
	}
	
	private int x;
	private int y;
	
	protected Command parse(String[] words) throws CommandParseException{
		if (matchCommandName(words[0])) {
			if (words.length != 3) {
				throw new CommandParseException("[ERROR]: " + INCORRECT_NUMBER_OF_ARGS_MSG + " for " + NAME + " command: " + DETAILS);
			} else {
					
				this.x = Integer.parseInt(words[2]);
				this.y = Integer.parseInt(words[1]);
				
				return this;
			}
		}
		return null;
	}

	@Override
	public int cost() {
		
		return 3;
	}
	
	private void coords(int widht) throws InvalidPositionException {
		
		if(this.x < 0 || this.x > widht) throw new InvalidPositionException("Invalid position.");
	}
}
