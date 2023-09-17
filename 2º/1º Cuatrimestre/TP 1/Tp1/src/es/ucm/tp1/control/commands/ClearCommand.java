package es.ucm.tp1.control.commands;

import es.ucm.tp1.control.exceptions.CommandExecuteException;
import es.ucm.tp1.logic.Game;

public class ClearCommand extends Command{

	private static final String NAME = "clear";

	private static final String DETAILS = "clear [0]";

	private static final String SHORTCUT = "0";

	private static final String HELP = "clear the road";
	
	
	public ClearCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}


	@Override
	public boolean execute(Game game) throws CommandExecuteException{
		
		game.clear();
		return true;
	}
	
	
	
}
