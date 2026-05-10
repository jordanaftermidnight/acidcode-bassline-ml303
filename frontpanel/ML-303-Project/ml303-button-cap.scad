// ML-303 Custom Button Cap for 12x12mm Tactile Switches
// OpenSCAD Design File
// 
// Instructions:
// 1. Adjust parameters below for your specific switches
// 2. Export as STL for 3D printing
// 3. Print with 0.1-0.2mm layer height for smooth finish

// Global Parameters (all dimensions in mm)
$fn = 64; // Resolution for curved surfaces

// Button cap dimensions
cap_width = 11.5;        // Slightly smaller than 12mm for clearance
cap_height = 11.5;       // Square cap
cap_thickness = 2.5;     // Top thickness
cap_total_height = 5.0;  // Total height of cap
corner_radius = 1.0;     // Rounded corners
top_dome = 0.3;          // Slight dome on top for better feel

// Stem dimensions (fits inside switch actuator)
stem_outer = 3.8;        // Outer diameter of stem
stem_inner = 3.4;        // Inner diameter for flexibility
stem_height = 3.5;       // How deep stem goes into switch
stem_split = 0.3;        // Split width for flexibility

// Text/marking options
enable_text = true;      // Set to false to disable text
text_string = "1";       // Change for different buttons
text_size = 4;           // Text size
text_depth = 0.3;        // How deep text is embossed

// Texture options
enable_grip = true;      // Add grip texture
grip_depth = 0.2;        // Depth of grip lines

// Main button cap module
module button_cap() {
    difference() {
        union() {
            // Main cap body
            translate([0, 0, cap_total_height/2])
                rounded_cube(cap_width, cap_height, cap_total_height, corner_radius);
            
            // Stem
            translate([0, 0, -stem_height/2])
                split_stem();
        }
        
        // Dome top (subtle curve)
        if (top_dome > 0) {
            translate([0, 0, cap_total_height + 20])
                sphere(r = 40);
        }
        
        // Text embossing
        if (enable_text) {
            translate([0, 0, cap_total_height - text_depth])
                linear_extrude(height = text_depth + 0.1)
                    text(text_string, size = text_size, halign = "center", valign = "center");
        }
        
        // Grip texture
        if (enable_grip) {
            for (i = [-4:2:4]) {
                translate([i, -cap_height/2, cap_total_height - grip_depth])
                    cube([0.5, cap_height, grip_depth + 0.1], center = false);
            }
        }
    }
}

// Rounded cube module
module rounded_cube(width, height, depth, radius) {
    hull() {
        for (x = [-1, 1]) {
            for (y = [-1, 1]) {
                translate([x * (width/2 - radius), y * (height/2 - radius), 0])
                    cylinder(r = radius, h = depth, center = true);
            }
        }
    }
}

// Split stem for flexibility
module split_stem() {
    difference() {
        // Main stem cylinder
        cylinder(d = stem_outer, h = stem_height, center = true);
        
        // Hollow center for flexibility
        cylinder(d = stem_inner, h = stem_height + 0.1, center = true);
        
        // Cross splits for spring action
        cube([stem_split, stem_outer + 0.1, stem_height + 0.1], center = true);
        cube([stem_outer + 0.1, stem_split, stem_height + 0.1], center = true);
    }
}

// Generate array of caps for printing multiple
module cap_array(rows, cols, spacing) {
    for (row = [0:rows-1]) {
        for (col = [0:cols-1]) {
            translate([col * spacing, row * spacing, 0])
                button_cap();
        }
    }
}

// Single cap (default)
button_cap();

// Uncomment below to generate a 4x4 array
// cap_array(4, 4, 13);

// Print settings recommendations:
// - Layer height: 0.15mm
// - Infill: 50%
// - Support: None needed
// - Print orientation: Cap facing up
// - Material: PLA or PETG
// - Nozzle temp: 210°C (PLA) / 240°C (PETG)