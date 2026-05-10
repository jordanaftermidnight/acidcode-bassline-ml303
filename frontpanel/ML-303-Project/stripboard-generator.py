#!/usr/bin/env python3
"""
ML-303 Stripboard Layout Generator
==================================
Generates ASCII stripboard layouts for ML-303 button adapters and circuits
"""

import sys
from typing import List, Tuple, Dict, Optional
from dataclasses import dataclass
from enum import Enum

class ComponentType(Enum):
    """Types of components that can be placed on stripboard"""
    RESISTOR = "R"
    CAPACITOR = "C"
    WIRE = "W"
    IC = "IC"
    CRYSTAL = "X"
    BUTTON = "B"
    DIODE = "D"
    LED = "L"
    HEADER = "H"
    CUT = "CUT"

@dataclass
class Component:
    """Represents a component on the stripboard"""
    type: ComponentType
    start: Tuple[int, int]  # (row, col)
    end: Optional[Tuple[int, int]] = None  # For multi-hole components
    value: str = ""
    orientation: str = "H"  # H=Horizontal, V=Vertical

@dataclass
class StripboardDesign:
    """Complete stripboard design with components and connections"""
    width: int
    height: int
    components: List[Component]
    cuts: List[Tuple[int, int]]  # Track cuts
    title: str = "Stripboard Layout"
    
class StripboardGenerator:
    """Generates ASCII representations of stripboard layouts"""
    
    def __init__(self):
        self.hole_char = "o"
        self.cut_char = "X"
        self.track_char = "="
        self.wire_chars = {
            "H": "-",  # Horizontal wire
            "V": "|",  # Vertical wire
            "D": "\\", # Diagonal
            "U": "/"   # Diagonal up
        }
        
    def generate_board(self, design: StripboardDesign) -> str:
        """Generate complete ASCII representation of stripboard"""
        output = []
        
        # Title
        output.append(design.title)
        output.append("=" * len(design.title))
        output.append("")
        
        # Component side view
        output.append("COMPONENT SIDE VIEW:")
        output.append("-------------------")
        comp_grid = self._create_component_grid(design)
        output.extend(self._format_grid(comp_grid, design))
        output.append("")
        
        # Track side view
        output.append("TRACK SIDE VIEW (Bottom):")
        output.append("------------------------")
        track_grid = self._create_track_grid(design)
        output.extend(self._format_grid(track_grid, design, bottom=True))
        output.append("")
        
        # Component list
        output.append("COMPONENTS:")
        output.append("-----------")
        output.extend(self._generate_component_list(design))
        output.append("")
        
        # Build instructions
        output.append("BUILD INSTRUCTIONS:")
        output.append("------------------")
        output.extend(self._generate_instructions(design))
        
        return "\n".join(output)
    
    def _create_component_grid(self, design: StripboardDesign) -> List[List[str]]:
        """Create grid showing component placement"""
        grid = [[self.hole_char for _ in range(design.width)] for _ in range(design.height)]
        
        # Add cuts
        for row, col in design.cuts:
            if 0 <= row < design.height and 0 <= col < design.width:
                grid[row][col] = self.cut_char
        
        # Add components
        for comp in design.components:
            self._place_component(grid, comp)
            
        return grid
    
    def _create_track_grid(self, design: StripboardDesign) -> List[List[str]]:
        """Create grid showing copper tracks"""
        grid = [[self.track_char for _ in range(design.width)] for _ in range(design.height)]
        
        # Remove tracks where cuts exist
        for row, col in design.cuts:
            if 0 <= row < design.height and 0 <= col < design.width:
                # Cut affects entire track on that row
                for c in range(design.width):
                    if grid[row][c] == self.track_char:
                        grid[row][c] = " "
                # Show cut position
                grid[row][col] = self.cut_char
                
        return grid
    
    def _place_component(self, grid: List[List[str]], comp: Component):
        """Place a component on the grid"""
        row, col = comp.start
        
        if comp.type == ComponentType.WIRE:
            # Draw wire connection
            if comp.end:
                self._draw_wire(grid, comp.start, comp.end)
            else:
                grid[row][col] = "+"
                
        elif comp.type == ComponentType.IC:
            # Draw IC with pin numbers
            if comp.end:
                # IC spans multiple holes
                for r in range(comp.start[0], comp.end[0] + 1):
                    for c in range(comp.start[1], comp.end[1] + 1):
                        if 0 <= r < len(grid) and 0 <= c < len(grid[0]):
                            grid[r][c] = "#"
                            
        elif comp.type == ComponentType.RESISTOR:
            # Draw resistor
            if comp.orientation == "H" and comp.end:
                for c in range(comp.start[1], comp.end[1] + 1):
                    if 0 <= c < len(grid[0]):
                        grid[row][c] = "R" if c == comp.start[1] else "="
            elif comp.orientation == "V" and comp.end:
                for r in range(comp.start[0], comp.end[0] + 1):
                    if 0 <= r < len(grid):
                        grid[r][col] = "R" if r == comp.start[0] else "|"
                        
        elif comp.type == ComponentType.CAPACITOR:
            grid[row][col] = "C"
            
        elif comp.type == ComponentType.BUTTON:
            # Draw button footprint
            if comp.end:
                for r in range(comp.start[0], comp.end[0] + 1):
                    for c in range(comp.start[1], comp.end[1] + 1):
                        if 0 <= r < len(grid) and 0 <= c < len(grid[0]):
                            grid[r][c] = "B"
                            
        else:
            # Default single-point component
            grid[row][col] = comp.type.value
    
    def _draw_wire(self, grid: List[List[str]], start: Tuple[int, int], end: Tuple[int, int]):
        """Draw a wire connection between two points"""
        r1, c1 = start
        r2, c2 = end
        
        if r1 == r2:  # Horizontal wire
            for c in range(min(c1, c2), max(c1, c2) + 1):
                if 0 <= c < len(grid[0]):
                    grid[r1][c] = self.wire_chars["H"]
        elif c1 == c2:  # Vertical wire
            for r in range(min(r1, r2), max(r1, r2) + 1):
                if 0 <= r < len(grid):
                    grid[r][c1] = self.wire_chars["V"]
    
    def _format_grid(self, grid: List[List[str]], design: StripboardDesign, bottom: bool = False) -> List[str]:
        """Format grid with row/column labels"""
        output = []
        
        # Column numbers
        col_label = "     "
        for i in range(design.width):
            col_label += f"{i+1:3}"
        output.append(col_label)
        
        # Separator
        output.append("   +" + "---+" * design.width)
        
        # Rows with labels
        for i, row in enumerate(grid):
            row_label = chr(65 + i)  # A, B, C, etc.
            row_str = f" {row_label} |"
            for cell in row:
                row_str += f" {cell} |"
            output.append(row_str)
            output.append("   +" + "---+" * design.width)
            
        return output
    
    def _generate_component_list(self, design: StripboardDesign) -> List[str]:
        """Generate component list with positions"""
        comp_list = []
        comp_count = {}
        
        for comp in design.components:
            # Count components by type
            key = f"{comp.type.name}_{comp.value}"
            comp_count[key] = comp_count.get(key, 0) + 1
            
            # Format position
            pos = f"{chr(65 + comp.start[0])}{comp.start[1] + 1}"
            if comp.end:
                pos += f"-{chr(65 + comp.end[0])}{comp.end[1] + 1}"
                
            comp_list.append(f"- {comp.type.name} {comp.value}: {pos}")
        
        # Add summary
        comp_list.append("")
        comp_list.append("Total components:")
        for key, count in sorted(comp_count.items()):
            comp_list.append(f"- {key}: {count}")
            
        return comp_list
    
    def _generate_instructions(self, design: StripboardDesign) -> List[str]:
        """Generate step-by-step build instructions"""
        instructions = []
        
        instructions.append(f"1. Cut stripboard to {design.height} rows x {design.width} columns")
        instructions.append("")
        
        if design.cuts:
            instructions.append("2. Make track cuts at:")
            for i, (row, col) in enumerate(design.cuts):
                instructions.append(f"   - {chr(65 + row)}{col + 1}")
            instructions.append("")
            
        instructions.append("3. Install components in this order:")
        instructions.append("   a) Wire jumpers")
        instructions.append("   b) Resistors")
        instructions.append("   c) Capacitors")
        instructions.append("   d) IC sockets")
        instructions.append("   e) Headers and connectors")
        instructions.append("")
        
        instructions.append("4. Check all connections with multimeter")
        instructions.append("5. Install ICs last (after power test)")
        
        return instructions

# Pre-defined ML-303 layouts
def create_3pin_adapter() -> StripboardDesign:
    """Create layout for 3-pin to 4-pin button adapter"""
    components = [
        Component(ComponentType.BUTTON, (1, 0), (2, 1), "12x12mm"),
        Component(ComponentType.WIRE, (1, 1), (1, 5), "Bridge"),
        Component(ComponentType.WIRE, (2, 1), (2, 6), "Bridge"),
        Component(ComponentType.HEADER, (1, 7), None, "3-pin"),
        Component(ComponentType.HEADER, (2, 7), None, "3-pin"),
        Component(ComponentType.HEADER, (2, 5), None, "3-pin"),
    ]
    
    cuts = [(0, 4), (1, 4), (2, 4), (3, 4)]
    
    return StripboardDesign(
        width=10,
        height=4,
        components=components,
        cuts=cuts,
        title="ML-303 3-PIN BUTTON ADAPTER"
    )

def create_matrix_controller() -> StripboardDesign:
    """Create layout for ATmega328P matrix controller"""
    components = [
        Component(ComponentType.IC, (4, 0), (13, 0), "ATmega328P"),
        Component(ComponentType.RESISTOR, (0, 2), (0, 4), "10K", "H"),
        Component(ComponentType.RESISTOR, (0, 6), (0, 8), "10K", "H"),
        Component(ComponentType.RESISTOR, (0, 10), (0, 12), "10K", "H"),
        Component(ComponentType.RESISTOR, (1, 2), (1, 4), "10K", "H"),
        Component(ComponentType.RESISTOR, (1, 6), (1, 8), "10K", "H"),
        Component(ComponentType.RESISTOR, (1, 10), (1, 12), "10K", "H"),
        Component(ComponentType.CRYSTAL, (8, 2), (8, 4), "16MHz", "H"),
        Component(ComponentType.CAPACITOR, (8, 2), None, "22pF"),
        Component(ComponentType.CAPACITOR, (8, 4), None, "22pF"),
        Component(ComponentType.HEADER, (15, 0), (15, 19), "40-pin", "H"),
    ]
    
    cuts = []
    for row in range(4, 14):
        cuts.append((row, 10))
    
    return StripboardDesign(
        width=30,
        height=20,
        components=components,
        cuts=cuts,
        title="ML-303 BUTTON MATRIX CONTROLLER"
    )

def main():
    """Main function to generate layouts"""
    generator = StripboardGenerator()
    
    # Generate adapter layout
    print("Generating 3-pin adapter layout...")
    adapter = create_3pin_adapter()
    adapter_output = generator.generate_board(adapter)
    
    with open("/Users/jordan_after_midnight/Desktop/ML-303-Project/GENERATED-LAYOUTS/adapter-layout.txt", "w") as f:
        f.write(adapter_output)
    
    # Generate matrix controller layout
    print("Generating matrix controller layout...")
    matrix = create_matrix_controller()
    matrix_output = generator.generate_board(matrix)
    
    with open("/Users/jordan_after_midnight/Desktop/ML-303-Project/GENERATED-LAYOUTS/matrix-layout.txt", "w") as f:
        f.write(matrix_output)
    
    print("Layouts generated successfully!")
    print("Check GENERATED-LAYOUTS/ directory for output files")

if __name__ == "__main__":
    # Create output directory
    # Create output directory
    import os
    os.makedirs("/Users/jordan_after_midnight/Desktop/ML-303-Project/GENERATED-LAYOUTS", exist_ok=True)
    main()