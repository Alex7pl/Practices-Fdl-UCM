package es.ucm.tp1.control.commands;

import es.ucm.tp1.control.exceptions.CommandExecuteException;
import es.ucm.tp1.logic.Game;

public class ExitCommand extends Command {

	private static final String NAME = "exit";

	private static final String DETAILS = "[e]xit";

	private static final String SHORTCUT = "e";

	private static final String HELP = "exit game";

	public ExitCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) throws CommandExecuteException{
		
		game.exit();
		return false;
	}

}
